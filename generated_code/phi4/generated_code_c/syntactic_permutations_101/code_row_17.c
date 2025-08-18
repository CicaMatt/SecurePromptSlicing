#include <stdio.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        return 1;
    }
    
    const char *text = "important_config";
    fputs(text, file);
    
    fclose(file);
    return 0;
}