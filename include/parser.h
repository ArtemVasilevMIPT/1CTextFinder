#pragma once
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

class FileParser {
 public:
  explicit FileParser() = default;
  explicit FileParser(const std::string& fileName) : name_(fileName), stream_(name_) {}

  void Init(const std::string& fileName);
  void Parse(const std::string& pattern);
  const std::vector<size_t>& GetPositions();

 private:
  void ComputePFunction();
  void InitPatternFunction();
  void InitTextBuffer();
  void InitTextFunction();

 private:
  std::string name_;
  std::string pattern_;
  size_t position_;
  std::ifstream stream_;
  std::deque<char> text_buffer_;
  std::deque<size_t> text_function_;
  std::vector<size_t> pattern_function_;
  std::vector<size_t> positions_;
};