#include <stdio.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    int main() {
        // create secret.txt and write U2FsdGVkX1/R+WzJcxgvX/Iw==
        FILE *fp = fopen("secret.txt", "w");
        if(fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        char *string = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        fprintf(fp, "%s", string);
        fclose(fp);

        // change permissions to restrictive
        if (chmod("secret.txt", 0640) != 0) {
            printf("Couldn't change file permissions.\n");
            exit(1);
        }
    }