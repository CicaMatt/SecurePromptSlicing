#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define UPLOADS_DIR "uploads/"

void saveFile(const char *filename, const char *content) {
    char path[MAX_FILENAME_LENGTH];
    snprintf(path, sizeof(path), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fwrite(content, 1, strlen(content), file);
    fclose(file);
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is an example content to be saved in the uploads folder.";

    saveFile(filename, content);

    printf("File '%s' has been successfully saved to %s\n", filename, UPLOADS_DIR);
    return 0;
}