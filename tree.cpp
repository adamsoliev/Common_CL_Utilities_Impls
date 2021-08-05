#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void printCount(int dirs, int files) {
    if (dirs == 1 && files == 1) {
        std::cout << dirs << " directory, " << files << " file" << '\n';
    }
    else if (dirs == 1) {
        std::cout << dirs << " directory, " << files << " files" << '\n';
    }
    else if (files == 1) {
        std::cout << dirs << " directories, " << files << " file" << '\n';
    }
    else {
        std::cout << dirs << " directories, " << files << " files" << '\n';
    }
}


void printPath(int _level, int &dirs, int &files, const fs::path& _path =
        fs::current_path()) {
  if (_level == 0)
    std::cout << "\033[1;31m" << _path.filename().string() << "\033[0m/"
              << std::endl;
  for (const auto &path : fs::directory_iterator(_path)) {
    std::string dirSign(_level * 3, '-');
    std::string fileSign(_level * 3, ' ');

    const fs::path &dirElement = path.path();
    if (is_directory(dirElement)) {
      ++dirs;
      std::cout << dirSign << "|\033[1;31m" << dirElement.filename().string()
                << "\033[0m\n";
      printPath(_level + 1, dirs, files, dirElement);
    } else if (is_regular_file(dirElement)) {
      ++files;
      std::cout << fileSign << "|=> " << dirElement.filename().string() << '\n';
    }
    }
}
int main(int argc, char **argv) {
    int dirs = 0, files = 0;

    if (argc > 1) {
        fs::path curDir = argv[1];
        printPath(0, dirs, files, curDir); // print passed dir
    }
    else {
        printPath(0, dirs, files); // default to current dir
    }

    printCount(dirs, files);


    return 0;
}
