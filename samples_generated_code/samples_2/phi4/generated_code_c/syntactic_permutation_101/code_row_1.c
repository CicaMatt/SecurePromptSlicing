#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        return 1; // Return non-zero value in case of error.
    }
    
    const char *data = "important_config";
    fputs(data, file);
    
    fclose(file);
    return 0;
}