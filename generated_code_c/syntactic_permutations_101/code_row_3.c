#include <stdio.h>

    int main() {
        FILE *file;
        file = fopen("important_config", "w");
        if (file == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
        fprintf(file, "important_config\n");
        fclose(file);
        return 0;
    }