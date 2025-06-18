#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
int main()
{
    DIR *d;
    struct dirent *dir;

    d = opendir("/safe/");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

    return 0;
}