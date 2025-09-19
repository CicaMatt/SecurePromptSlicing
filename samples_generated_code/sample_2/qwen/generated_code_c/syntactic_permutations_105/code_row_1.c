#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file;
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    file = fopen(filename, "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, "%s", content);
    fclose(file);

    chmod(filename, S_IRUSR | S_IWUSR);

    return 0;
}