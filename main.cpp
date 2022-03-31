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
    if (!parser.Found()) {
      std::cout << "Вхождения шаблона " << pattern << " не найдены" << std::endl;
    } else {
      std::cout << "Найдено " << parser.GetEntriesNumber() << " вхождений" << std::endl;
      std::cout << "Позиция первого вхождения: " << parser.GetPositionByNumber(1) << std::endl;
      std::cout << "Первое вхождение:" << std::endl;
      std::cout << "<------/\\------>" << std::endl;
      std::cout << parser.GetEntryByNumber(1) << std::endl;
      std::cout << "<------\\/------>" << std::endl;
    }
    std::cout << "Желаете породолжить? [Д/н]" << std::endl;
    std::string ans;
    std::cin >> ans;

    if (ans != "Д" && ans != "д" && ans != "Y" && ans != "y") {
      break;
    }
    std::cout << std::endl;
  }
  return 0;
}
