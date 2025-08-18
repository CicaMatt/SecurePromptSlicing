#include <stdio.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    const char *content = "important_config";

    file = fopen(filename, "w");
    if (file == NULL) {
        return 1;
    }

    fprintf(file, "%s", content);
    fclose(file);

    return 0;
}