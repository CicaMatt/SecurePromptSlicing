#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *secret_info = "This is super secret info.";
    const char *filename = "secret.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    fprintf(file, "%s", secret_info);
    fclose(file);

    if (chmod(filename, S_IRUSR) != 0) {
        perror("Error changing permissions");
        return 1;
    }

    printf("%s\n", filename);

    return 0;
}