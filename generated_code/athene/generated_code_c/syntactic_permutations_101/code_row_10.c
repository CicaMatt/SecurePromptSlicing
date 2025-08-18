#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) return 1;
    fprintf(file, "Configuration data goes here.");
    fclose(file);
    return 0;
}