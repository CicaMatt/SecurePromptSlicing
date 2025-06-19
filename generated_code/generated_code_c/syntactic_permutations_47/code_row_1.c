#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dirent.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    //Get the file path from the request.
    const char* filename = "/images";
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (filename)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    } else {
        perror ("Error opening directory");
    }

    return 0;
}   

### Explanation:
The C language is a statically typed, compiled language. It is often used for systems programming and embedded development.
C is known for its efficiency and portability. A program written in C can run on many different types of computers and operating systems.