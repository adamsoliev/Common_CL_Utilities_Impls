#include <bitset>
#include <iostream>
#include <string>
#include <unordered_map>

template <typename T> //
inline void prettyPrintBits(T input) {
  std::bitset<sizeof(T) * 8> bits(input);
  for (int i = bits.size() - 1; i >= 0; --i) {
    std::cout << bits[i];
    if (i % 4 == 0 && i != 0)
      std::cout << "_";
  }
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      std::string s(argv[i]);

      if (s[0] == '-' && s[1] == 'i') {
        // parse int
        std::cout << "int: ";
        prettyPrintBits(std::stoi(s.substr(2)));
      } else if (s[0] == '-' && s[1] == 'l') {
        // parse long
        std::cout << "long int: ";
        prettyPrintBits(std::stol(s.substr(2)));
      } else if (s[0] == '-' && s[1] == 'c') {
        // parse char
        std::cout << "char: ";
        prettyPrintBits(s[2]);
      } else if (s[0] == '-' && s[1] == 'b') {
        // parse bool
        std::cout << "bool: ";
        // TODO: maybe there is a better way to do this
        if (s[2] == 't')
          prettyPrintBits(true);
        else
          prettyPrintBits(false);
      } else if (s == "--help") {
        // print help message
        std::cout << "USAGE: [FILE] [OPTION]" << std::endl;
        std::cout << "\t-i[INT]             binary representation of [INT]"
                  << std::endl;
        std::cout << "\t-l[LONG INT]        binary representation of [LONG INT]"
                  << std::endl;
        std::cout << "\t-c[CHAR]            binary representation of [CHAR]"
                  << std::endl;
        std::cout << "\t-b[BOOL]            binary representation of [BOOL]"
                  << std::endl;
      }
    }
    return 0;
  }

  std::cout << "No input passed" << std::endl;
  return 0;
}
