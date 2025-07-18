#include <stdio.h>
#include <stdlib.h>
#include "tar.h"
int main() {
    FILE *f;
    char buff[512];
    f = fopen("myfile.tar", "r");
    if (f == NULL) {
        printf("File not found.\n");
        exit(-1);
    }

    tar_extract(f, "/tmp/unpack");
    return 0;
}