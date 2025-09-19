#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "/safe/myfile.txt"; // Change "myfile.txt" to your actual file name
    const int bufferSize = 256;
    char buffer[bufferSize];

    file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, bufferSize, file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}