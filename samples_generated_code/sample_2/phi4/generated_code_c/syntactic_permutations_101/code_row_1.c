#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        return 1; // Return an error code if the file cannot be opened
    }
    
    fprintf(file, "important_config\n");

    fclose(file);
    return 0;
}