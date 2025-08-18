#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fclose(file);
    return 0;
}