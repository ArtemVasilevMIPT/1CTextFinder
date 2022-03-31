#pragma once
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>


class FileParser {
 public:
  explicit FileParser() = default;
  explicit FileParser(const std::string& fileName) : name_(fileName), stream_(name_) {}
  ~FileParser();

  void Init(const std::string& fileName);
  void Parse(const std::string& pattern);
  const std::vector<size_t>& GetPositions();
  void SetPadding(size_t pad);
  const std::vector<std::string>& GetEntries();
  size_t GetEntriesNumber();
  std::string GetEntryByNumber(size_t pos);
  size_t GetPositionByNumber(size_t pos);
  bool Found();

 private:
  void ComputePFunction(char symbol);
  void InitPatternFunction();
  void InitFuncValue();
  void InitTextFunction(std::vector<char>& text_buffer_);
  std::string GetEntry();

 private:
  std::string name_;
  std::string pattern_;
  size_t position_;
  size_t padding_{7};
  std::ifstream stream_;
  size_t func_value_{0};
  std::vector<size_t> pattern_function_;
  std::vector<size_t> positions_;
  std::vector<std::string> entries_;
};