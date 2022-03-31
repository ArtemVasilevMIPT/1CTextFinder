#include "parser.h"
#include <chrono>

int main() {
  std::cout << "Данный пример ищет позицию первого вхождения шаблона 'Казак' в тексте романа Тихий Дон" << std::endl;
  FileParser parser("examples/Data/Tihiy_Don.txt");

  // Start timer
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  parser.Parse("Казак");

  // Stop timer
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  size_t pos = parser.GetPositions()[0];

  std::cout << "Позиция первого вхождения слова 'Казак': " << pos << std::endl;
  std::cout << "Поиск занял " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
            << " мкс" << std::endl;
  return 0;
}



