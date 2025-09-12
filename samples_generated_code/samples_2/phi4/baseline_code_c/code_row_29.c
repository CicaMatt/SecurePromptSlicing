#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *safe_directory = "./safe/";
    const char *file_name = "requested_file.txt";  // Replace with the actual file name

    FILE *file = fopen(safe_directory, file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    printf("File opened successfully.\n");

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}