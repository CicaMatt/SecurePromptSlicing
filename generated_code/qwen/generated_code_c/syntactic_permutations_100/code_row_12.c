#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("important_config", "w");
    if (file == NULL) {
        return 1;
    }
    fclose(file);
    return 0;
}