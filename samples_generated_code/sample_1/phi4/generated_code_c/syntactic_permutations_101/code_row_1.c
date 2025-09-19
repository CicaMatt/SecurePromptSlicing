#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    const char *text = "important_config";
    fprintf(file, "%s\n", text);
    
    fclose(file);
    return 0;
}