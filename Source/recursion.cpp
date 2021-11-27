#include <dirent.h>
#include <cstdio>
#include <sys/stat.h>

#include <string>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iostream>
// Huh

#define OPEN_DIR_PREFIX std::string("OpenDir: ")
#define RED_DIR_PREFIX std::string("ReadDir: ")
#define CLOSE_DIR_PREFIX std::string("CloseDir: ")
#define RENAME_PREFIX std::string("Rename: ")
#define FILE_STAT_PREFIX std::string("FileStat: ")
#define REGULAR_TYPE 4
#define DIR_TYPE 16

using namespace std;

void walkdir(string dir_name);

string as_string(long long t);

string last_error();

int main33() {
    string dir_name("../test"); // default dir

    walkdir(dir_name);

    return 0;
}

void walkdir(string dir_name) {
    DIR *dir = opendir(dir_name.c_str()); // open dir
    cout << "[LOGGER] Opening dir: '" << dir_name << "'" << endl;
    if (dir == nullptr)
        throw std::runtime_error(
                OPEN_DIR_PREFIX + last_error() + " (" + dir_name + ")");  // check, if result null, throw an error

    errno = 0; // clear error
    struct dirent *dir_entry = readdir(dir); // create dirent
    // check first
    // errno must be null sometimes
    while (dir_entry) {
        errno = 0;
        dir_entry = readdir(dir); // read dir/dir_entry
        string name(dir_entry->d_name); // define name as string (not full name)
        string full_name(dir_name + '/' + name);

        if (errno != 0)
            throw std::runtime_error(
                    RED_DIR_PREFIX + last_error() + " (" + dir_name + ")"); // If any error acquired while reading, check and throw error

        if (name != "." && name != "..") { // Else we check is name not equals "." and ".."

            struct stat file_stat; // create dir_entry stat structure, define it as null by default

            // check stat, if not success, throw an exception
            if (!stat(dir_entry->d_name, &file_stat)) {
                throw std::runtime_error(
                        FILE_STAT_PREFIX + last_error());
            } // Check is stat null, if null, throw an exception

            if (dir_entry->d_type == DIR_TYPE) {
                cout << "[LOGGER] Founded dir '" << full_name << "', starting recursive walking..." << endl;
                walkdir(full_name);
                continue;
            }

            if (dir_entry->d_type !=
                REGULAR_TYPE) { // dir_entry type is regular
                if (name.find('_') == string::npos) continue; // if name doesn't contain required symbol, skip element

                string new_name(full_name + as_string(file_stat.st_size)); // create new name

                // print info
                cout << "[LOGGER] File '" << name << "' ('" << full_name << "') size: " << file_stat.st_size << " bytes"
                     << endl;
                cout << "[LOGGER] New name will be: " << new_name << endl;

                if (rename(full_name.c_str(), new_name.c_str())) // rename
                    throw std::runtime_error(RENAME_PREFIX + last_error()); // If any error, throw exception
                else
                    cout << "[LOGGER] Renamed: " << full_name << ", New name: " << new_name
                         << endl; // print success message
            }
        }
    }
    if (closedir(dir) != 0)
        throw std::runtime_error(CLOSE_DIR_PREFIX + last_error()); // Check is there any error while closing
    // dir, throw error if yes
}

string last_error() {
    int buf = errno; // take errno into buffer

    errno = 0; // clear error

    return std::strerror(buf); // return error
}

string as_string(long long t) // convert any type to string using stringstream
{
    stringstream s; // create stream
    s << t; // fill with t
    return s.str(); // make string
}