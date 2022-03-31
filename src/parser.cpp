#include "../include/parser.h"
#include <string>

void FileParser::Init(const std::string& fileName) {
  if(stream_.is_open()) {
    stream_.close();
  }

  stream_.open(fileName);
}

void FileParser::InitFuncValue() {
  std::vector<char> text_buffer;

  for (size_t i = 0; i < pattern_.size(); ++i) {
    char c = stream_.get();
    if (std::char_traits<char>::not_eof(c)) {
      text_buffer.push_back(c);
    } else {
      break;
    }
  }
  position_ = text_buffer.size() + 1;
  InitTextFunction(text_buffer);
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

void FileParser::InitTextFunction(std::vector<char>& text_buffer_) {
  std::vector<size_t> text_function_(text_buffer_.size(), 0);

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
  func_value_ = text_function_.back();
}

void FileParser::ComputePFunction(char symbol) {
  size_t i = pattern_.size() - 1;
  size_t k = (i == 0) ? 0 : func_value_;
  while (k > 0 && symbol != pattern_[k]) {
    k = pattern_function_[k - 1];
  }
  if (symbol == pattern_[k]) {
    ++k;
  }
  func_value_ = k;

  if(k == pattern_.size()) {
    entries_.push_back(GetEntry());
    positions_.push_back(position_);
  }
}

void FileParser::Parse(const std::string &pattern) {
  pattern_ = pattern;
  positions_.clear();
  entries_.clear();

  InitPatternFunction();
  InitFuncValue();

  char c = stream_.get();
  while (std::char_traits<char>::not_eof(c)) {
    ComputePFunction(c);
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
void FileParser::SetPadding(size_t pad) {
  padding_ = pad;
}
std::string FileParser::GetEntry() {
  std::string buff;
  if (position_ < padding_ + pattern_.size()) {
    stream_.seekg(0);
  } else {
    stream_.seekg(position_ - padding_ - pattern_.size());
  }

  size_t readNum = 0;
  char c = stream_.get();
  while(std::char_traits<char>::not_eof(c) && readNum < 2 * padding_ + pattern_.size()) {
    buff.push_back(c);
    ++readNum;
    c = stream_.get();
  }

  stream_.seekg(position_);

  return buff;
}
const std::vector<std::string> &FileParser::GetEntries() {
  return entries_;
}

size_t FileParser::GetEntriesNumber() {
  return positions_.size();
}
std::string FileParser::GetEntryByNumber(size_t pos) {
  if (entries_.size() <= pos || pos <= 0) {
    throw std::runtime_error("Invalid entry number");
  } else {
    return entries_[pos - 1];
  }
}
size_t FileParser::GetPositionByNumber(size_t pos) {
  if (positions_.size() <= pos || pos <= 0) {
    throw std::runtime_error("Invalid entry number");
  } else {
    return positions_[pos - 1];
  }
}
bool FileParser::Found() {
  return !positions_.empty();
}
