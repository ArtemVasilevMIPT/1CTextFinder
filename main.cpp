#include <parser.h>

int main() {

  std::cout << "Введите путь к файлу: ";
  std::string path;
  std::cin >> path;

  FileParser parser;
  parser.Init(path);

  while (true) {
    std::string pattern;
    std::cout << "Введите шаблон" << std::endl;
    std::cin >> pattern;

    parser.Parse(pattern);

    auto pos = parser.GetPositions();

    std::cout << "Найдено " << pos.size() << " вхождений" << std::endl;

    std::cout << "Желаете породолжить? [Д/н]" << std::endl;
    std::string ans;
    std::cin >> ans;
    if (ans == "н" || ans == "n" || ans == "N" || ans == "Н") {
      break;
    }
  }
  return 0;
}
