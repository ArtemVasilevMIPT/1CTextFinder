#include "../include/parser.h"
#include <string>

void FileParser::Init(const std::string& fileName) {
  if(stream_.is_open()) {
    stream_.close();
  }

  stream_.open(fileName);
}

void FileParser::InitTextBuffer() {
  text_buffer_.clear();

  for (size_t i = 0; i < pattern_.size(); ++i) {
    char c = stream_.get();
    if (std::char_traits<char>::not_eof(c)) {
      text_buffer_.push_back(c);
    } else {
      break;
    }
  }
}

void FileParser::InitPatternFunction() {
  pattern_function_.clear();
  pattern_function_.resize(pattern_.size());

  pattern_function_[0] = 0;
  for (size_t i = 1; i < pattern_.size(); ++i) {
    size_t k = pattern_function_[i - 1];
    while (k > 0 && pattern_[i] != pattern_[k]) {
      k = pattern_function_[k - 1];
    }
    if (pattern_[i] == pattern_[k]) {
      ++k;
    }
    pattern_function_[i] = k;
  }
}

void FileParser::InitTextFunction() {
  text_function_.clear();
  text_function_.resize(text_buffer_.size());

  for (size_t i = 0; i < text_buffer_.size(); ++i) {
    size_t k = (i == 0) ? 0 : text_function_[i - 1];
    while (k > 0 && text_buffer_[i] != pattern_[k]) {
      k = pattern_function_[k - 1];
    }
    if (text_buffer_[i] == pattern_[k]) {
      ++k;
    }
    text_function_[i] = k;

    if(text_function_[i] == pattern_.size()) {
      positions_.push_back(i + 1);
    }
  }
}

void FileParser::ComputePFunction() {
  size_t i = text_buffer_.size() - 1;
  size_t k = (i == 0) ? 0 : text_function_[i];
  while (k > 0 && text_buffer_[i] != pattern_[k]) {
    k = pattern_function_[k - 1];
  }
  if (text_buffer_[i] == pattern_[k]) {
    ++k;
  }
  text_function_.push_back(k);
  text_function_.pop_front();

  if(k == pattern_.size()) {
    positions_.push_back(position_);
  }
}

void FileParser::Parse(const std::string &pattern) {
  pattern_ = pattern;
  positions_.clear();

  InitPatternFunction();
  InitTextBuffer();
  InitTextFunction();

  position_ = text_buffer_.size() + 1;

  char c = stream_.get();
  while (std::char_traits<char>::not_eof(c)) {
    text_buffer_.pop_front();
    text_buffer_.push_back(c);
    ComputePFunction();
    ++position_;
    c = stream_.get();
  }
  stream_.clear();
  stream_.seekg(0);// Rewind
}
const std::vector<size_t> &FileParser::GetPositions() {
  return positions_;
}
FileParser::~FileParser() {
  if (stream_.is_open()) {
    stream_.close();
  }
}
