#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char *secretInfo = "This is some super secret info.";
    const char *filename = "secret.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s", secretInfo);
    fclose(file);

    if (chmod(filename, S_IRUSR | S_IWUSR) != 0) {
        perror("Error changing permissions");
        return 1;
    }

    printf("%s\n", filename);

    return 0;
}