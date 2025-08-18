#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        return 1;
    }
    fprintf(file, ".\n"); // Write the dot character to the file
    fclose(file);
    return 0;
}