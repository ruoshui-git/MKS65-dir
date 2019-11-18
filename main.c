#include <stdio.h>
#include <string.h>

#include <errno.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(void)
{
    char * dir_path = "./";
    puts("Stat for dir: ./");

    int total_size = 0;

    struct dirent * file = NULL;
    DIR * ds = NULL;

    ds = opendir(dir_path);
    if (!ds)
    {
        report_error("Unable to open directory");
    }


    errno = 0;
    struct stat * info;
    while (true)
    {
        file = readdir(ds);
        if (!file)
        {
            if (errno != 0)
            {
                report_error("Unable to read from directory stream");
            }
            break;
        }
        if (file->d_type == DT_REG)
        {
            stat(file->d_name, info);
        }
        else if (file->d_type == DT_DIR)
        {
            print_dir(file->d_name);
        }
    }

}

void report_error(char * s, int e)
{
    printf("%s\n\tError %d: %s\n", s, e, strerror(e));
}
