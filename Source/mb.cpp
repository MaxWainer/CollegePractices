#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define DIR_TYPE 4
#define REG_TYPE 8

void clr_errno()
{
    errno = 0;
}

void walk_directory(char* dir_name);

int main3331()
{
    walk_directory("./test");
    return 0;
}

void walk_directory(char* dir_name)
{
    DIR * dir = opendir(dir_name);

    if (dir == NULL) {
        perror("OpenDir");
        clr_errno();
    } else {
        clr_errno();
        struct dirent *di;

        while ((di = readdir(dir))) {

            if (errno != 0) {
                perror("ReadDir");
                clr_errno();
            }

            if (di != NULL) {
                if (!(strcmp(di->d_name, ".") && strcmp(di->d_name, ".."))) continue;

                char full_name[256] = "";
                char del[256] = "/";

                strncpy(full_name, dir_name, strlen(dir_name));

                strcat(full_name, del);
                strcat(full_name, di->d_name);

                if (di->d_type == DIR_TYPE) {
                    walk_directory(full_name);
                }

                if (di->d_type == REG_TYPE) {
                    if(strstr(di->d_name, "!") != NULL) {
                        struct stat st;

                        if (stat(full_name, &st)) {
                            perror("stat");
                            clr_errno();
                        }
                        char n_str[256];
                        char num_str[256];
                        printf("dir_name: %s\n", dir_name);
                        strncpy(n_str, dir_name, strlen(dir_name)+1);

                        sprintf(num_str, "%li", st.st_size);
                        strcat(n_str, del);
                        strcat(n_str, num_str);
                        printf("New name: '%s' -> '%s'\n", full_name, n_str);
                        if (rename(full_name, n_str)) {
                            perror("rename");
                            printf("rename(%s, %s);\n", full_name, n_str);
                            clr_errno();
                        } else printf("Renamed '%s', to '%s'\n", full_name, n_str);
                    }
                }
            }
        }

        if (closedir(dir) != 0)
        {
            perror("CloseDir");
            clr_errno();
        }
    }
}