#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char *secret_info = "I'm Batman.";
    FILE *fp;
    fp = fopen("file.txt", "w+");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    chmod("file.txt", S_IRUSR);
    fprintf(fp, "%s", secret_info);
    fclose(fp);
    system("cat file.txt");
    return 0;
}