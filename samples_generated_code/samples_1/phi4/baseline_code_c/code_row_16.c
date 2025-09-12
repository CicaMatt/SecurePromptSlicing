#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "/safe/file.txt";
    char buffer[1024];
    
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}