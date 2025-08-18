#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char *secret = "SuperSecretInfo";
    FILE *file = fopen("secret.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(file, "%s", secret);
    fclose(file);

    if (chmod("secret.txt", S_IRUSR) != 0) {
        perror("Error changing permissions");
        return 1;
    }

    printf("File name: %s\n", "secret.txt");
    return 0;
}