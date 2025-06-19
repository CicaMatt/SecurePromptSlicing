#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"

int main() {
    cgiFilePtr fp;
    char name[128], filename[128];
    int ret;

    if(cgiFormFileName("upload", filename, sizeof(filename)) != cgiFormSuccess) {
        printf("No file uploaded");
        exit(1);
    }
    
    fp = cgiFileOpen(filename, "r");
    if(fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    ret = cgiFileRead(name, 128, 1, fp);
    if(ret != 0) {
        printf("Error reading file");
        exit(1);
    }

    cgiFileClose(fp);

    return 0;
}