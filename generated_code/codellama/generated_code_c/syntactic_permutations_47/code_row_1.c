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
