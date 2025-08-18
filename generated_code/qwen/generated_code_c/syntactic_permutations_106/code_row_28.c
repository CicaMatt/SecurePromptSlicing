#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *secret_info = "This is some super secret info.";
    const char *filename = "secret.txt";
    FILE *file;

    file = fopen(filename, "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "%s", secret_info);
    fclose(file);

    chmod(filename, S_IRUSR);

    printf("%s\n", filename);

    return 0;
}