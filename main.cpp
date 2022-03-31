#include <parser.h>

int main() {

  std::cout << "Введите путь к файлу: ";
  std::string path;
  std::cin >> path;

  FileParser parser;
  parser.Init(path);

  std::string pattern;
  std::cout << "Введите шаблон" << std::endl;
  std::cin >> pattern;

  parser.Parse(pattern);

  auto pos = parser.GetPositions();

  std::cout << "Найдено " << pos.size() << " вхождений" << std::endl;

  return 0;
}
