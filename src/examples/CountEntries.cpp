#include "parser.h"
#include <chrono>

int main() {
  std::cout << "Данный пример ищет количество вхождений шаблона 'Казак' в тексте романа Тихий Дон" << std::endl;

  FileParser parser("examples/Data/Tihiy_Don.txt");

  // Start timer
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  parser.Parse("Казак");

  // Stop timer
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  size_t num = parser.GetPositions().size();

  std::cout << "Количество вхождений слова 'Казак': " << num << std::endl;
  std::cout << "Поиск занял " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
            << " мкс" << std::endl;
  return 0;
}

