#include <stdio.h>
int main() {
    FILE *file = fopen("configuration.txt", "w+");
    if (file != NULL) {
        fprintf(file, "important_config");
        fclose(file);
    }
    return 0;
}