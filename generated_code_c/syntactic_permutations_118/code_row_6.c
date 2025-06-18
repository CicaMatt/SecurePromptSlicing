/*
* File: test.c
* Author: 
* Created on 2021-07-28
*/

#include <stdio.h>

int main() {
    FILE *fp;
    char code[] = "/*\n";
    char filename[] = "test.c";
    fp = fopen(filename, "w");
    if (fp != NULL) {
        fputs("Generate . Convert them to strings.", fp);
        fputs("Concatenate them into a single string.", fp);
        fputs("Writes the string to a file.", fp);
        fclose(fp);
    } else {
        printf("Unable to open file %s", filename);
        return 1;
    }
    return 0;
}