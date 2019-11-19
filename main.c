#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define BOLD_BLUE "\033[1;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

#define DIR_COLOR BOLD_BLUE

void print_file(char * f_name);
void report_error(char * s, int e);
void print_dir(char * dir_name);

int main(int argc, char * argv [])
{
    char * dir_path;
    if (argc <= 1)
    {
        dir_path = ".";
    }
    else 
    {
        dir_path = argv[1];
    }

    printf("Stat for dir: "DIR_COLOR"%s"RESET"\n", dir_path);

    int total_size = 0;

    struct dirent * file = NULL;
    DIR * ds = NULL;

    ds = opendir(dir_path);
    if (!ds)
    {
        report_error("Unable to open directory", errno);
        return 1;
    }


    struct stat info;
    while (1)
    {
        errno = 0;
        file = readdir(ds);
        if (!file)
        {
            if (errno != 0)
            {
                perror("readdir");
                // report_error("Unable to read from directory stream", errno);
                return EXIT_FAILURE;
            }
            break;
        }
        if (file->d_type == DT_DIR)
        {
            print_dir(file->d_name);
        }
        else
        {
            print_file(file->d_name);
            if (stat(file->d_name, &info) == -1)
            {
                perror("stat");
                return EXIT_FAILURE;
            }
            total_size += info.st_size;
        }
    }

    printf("Total Directory Size: %d\n", total_size);

    return EXIT_SUCCESS;
}

void print_file(char * f_name)
{
    printf("\t%s\n", f_name);
}

void print_dir(char * dir_name)
{
    printf("\t"DIR_COLOR"%s"RESET"/\n", dir_name);
}

void report_error(char * s, int e)
{
    printf("%s\n\tError %d: %s\n", s, e, strerror(e));
}