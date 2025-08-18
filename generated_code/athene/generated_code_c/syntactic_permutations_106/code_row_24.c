#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *secret = "SuperSecretInfo";
    FILE *fp = fopen("secretfile.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(fp, "%s", secret);
    fclose(fp);

    if (chmod("secretfile.txt", S_IRUSR) != 0) {
        perror("Error changing permissions");
        return EXIT_FAILURE;
    }

    printf("Secret written to file and permissions set.\n");
    return EXIT_SUCCESS;
}