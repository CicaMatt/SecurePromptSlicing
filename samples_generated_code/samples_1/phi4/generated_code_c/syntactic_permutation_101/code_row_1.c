#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        return 1;
    }
    fputs("important_config\n", file);
    fclose(file);
    return 0;
}