#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *secret = "SuperSecretInfo";
    FILE *fp;
    char filename[] = "secretfile.txt";

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%s", secret);
    fclose(fp);

    if (chmod(filename, 0444) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);

    return 0;
}