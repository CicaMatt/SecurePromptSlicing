#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }
    fclose(file);
    return 0;
}