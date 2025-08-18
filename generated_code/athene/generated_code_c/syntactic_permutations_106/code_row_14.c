#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *secret = "This is super secret info!";
    const char *filename = "secret.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s", secret);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing file permissions");
        return EXIT_FAILURE;
    }

    printf("%s\n", filename);
    return 0;
}