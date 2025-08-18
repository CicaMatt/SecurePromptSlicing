#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char *secret_info = "This is a super secret message!";
    FILE *fp;
    const char *filename = "secret.txt";

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(fp, "%s", secret_info);
    fclose(fp);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);
    return 0;
}