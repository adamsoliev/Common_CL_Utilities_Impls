#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

class Tree {
private:
    int dirs = 0;
    int files = 0;
    vector<string> inner_pointers = { "├── ", "│   " };
    vector<string> outer_pointers = { "└── ", "    " };

public:
    void walk(const string& directory, const string& prefix) {
        vector<fs::directory_entry> entries;

        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.path().filename().string()[0] != '.') {
                entries.push_back(entry);
            }
        }
        sort(entries.begin(), entries.end(), [](const fs::directory_entry
        &left, const fs::directory_entry &right) -> bool {
            return left.path().filename() < right.path().filename();
        });

        for (int i = 0; i < entries.size(); ++i) {
            fs::directory_entry entry = entries[i];
            vector<string> pointers = i == entries.size() - 1 ? outer_pointers
                    : inner_pointers;
            cout << prefix << pointers[0] << entry.path().filename().string()
            << endl;

            if (entry.is_directory()) {
                ++dirs;
                walk(entry.path(), prefix + pointers[1]);
            }
            else if (entry.is_regular_file()) {
                ++files;
            }
            // TODO: other types of files could also be added (e.g., links)
        }
    }

    void summary() const {
        cout << "\n" << dirs << " directories, " << files << " files" << endl;
    }
};




int main(int argc, char **argv) {
    Tree tree;
    // TODO: error check (wrong input, etc)
    string directory = argc == 1 ? "." : argv[1];

    cout << directory << endl;
    tree.walk(directory, "");
    tree.summary();

    return 0;
}
