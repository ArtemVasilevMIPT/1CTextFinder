#pragma once
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>


class FileParser {
 public:
  explicit FileParser() = default;
  explicit FileParser(const std::string& fileName) : stream_(fileName) {}
  ~FileParser();

  // Opens file
  void Init(const std::string& fileName);
  // Searches for a pattern in file
  void Parse(const std::string& pattern);
  // Sets the padding for a context
  void SetPadding(size_t pad);
  // Returns number of entries found in text
  size_t GetEntriesNumber();
  // Returns an entry by its number, starting from 1
  std::string GetEntryByNumber(size_t pos);
  // Returns an entry position by number, starting from 1
  size_t GetPositionByNumber(size_t pos);
  // Returns true if at least one entry has been found, false otherwise
  bool Found();
  // Checks if the file was opened successfully
  bool Opened();

 private:
  // Recomputes prefix function during the step on the algorithm
  void ComputePFunction(char symbol);
  // Computes prefix function for a pattern
  void InitPatternFunction();
  // Computes initial value of a prefix function
  void InitFuncValue();
  // Computes first |text_buffer_| values of prefix function
  void InitTextFunction(std::vector<char>& text_buffer_);
  // Returns an entry with its context
  std::string GetEntry();
  // Returns vector of entries positions
  const std::vector<size_t>& GetPositions();
  // Returns vector of entries
  const std::vector<std::string>& GetEntries();

 private:
  std::string pattern_;
  size_t position_;
  size_t padding_{7};
  std::ifstream stream_;
  size_t func_value_{0}; // The last value of a prefix function
  std::vector<size_t> pattern_function_;
  std::vector<size_t> positions_;
  std::vector<std::string> entries_;
};