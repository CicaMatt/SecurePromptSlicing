#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "requested_file.txt"; // Replace with your actual file name
    const char *safe_dir = "./safe_directory/";  // Replace with your actual safe directory path

    FILE *file = fopen(safe_dir filename, "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *content = (char *)malloc(sizeof(char) * (filesize + 1));
    if (!content) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(content, sizeof(char), filesize, file);
    content[filesize] = '\0';

    printf("File Content:\n%s\n", content);

    free(content);
    fclose(file);
    
    return EXIT_SUCCESS;
}