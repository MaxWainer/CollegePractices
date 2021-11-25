#include <dirent.h>
#include <cstdio>
#include <sys/stat.h>

#include <string>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iostream>

#define OPEN_DIR_PREFIX std::string("OpenDir: ")
#define RED_DIR_PREFIX std::string("ReadDir: ")
#define CLOSE_DIR_PREFIX std::string("CloseDir: ")
#define RENAME_PREFIX std::string("Rename: ")

using namespace std;

template<typename T>
string as_string(T t);

string last_error();

int main() {
    string dir_name(".");

    DIR *dir = opendir(dir_name.c_str()); // open dir
    if (dir == nullptr)
        throw std::runtime_error(
                OPEN_DIR_PREFIX + last_error() + " (" + dir_name + ")");  // check, if result null, throw an error

    errno = 0; // clear error
    struct dirent *dir_entry = readdir(dir); // create dirent
    do {
        dir_entry = readdir(dir); // read dir/dir_entry
        string name(dir_entry->d_name); // define name as string (full name)

        if (dir_entry == nullptr) continue; // check is dir/dir_entry null

        //if (errno != 0)
        //    throw std::runtime_error(
        //            RED_DIR_PREFIX + last_error()); // If any error acquired while reading, check and throw error

        if (name != "." && name != ".." &&
            (dir_entry->d_type != 4)) { // Else we check is name not equals "." and ".." and dir_entry type is regular
            if (!name.find("_")) continue; // if name doesn't contain required symbol, skip element

            struct stat file_stat; // create dir_entry stat structure
            stat(dir_entry->d_name, &file_stat); // fill stat

            string new_name(name + as_string(file_stat.st_size)); // create new name

            cout << "Renamed: " << name << ", New name: " << new_name << endl;

            //if (!
            //rename(dir_entry->d_name, new_name.c_str());
            //) // rename
            //throw std::runtime_error(RENAME_PREFIX + last_error()); // If any error, throw exception
        }
    } while (dir_entry);
    if (closedir(dir) != 0)
        throw std::runtime_error(CLOSE_DIR_PREFIX + last_error()); // Check is there any error while closing
    // dir, throw error if yes

    return 0;
}

string last_error()
{
    return std::strerror(errno);
}

template<typename T>
string as_string(T t) // convert any type to string using stringstream
{
    stringstream s; // create stream
    s << t; // fill with t
    return s.str(); // make string
}