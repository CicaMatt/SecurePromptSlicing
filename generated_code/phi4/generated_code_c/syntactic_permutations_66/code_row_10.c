#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

void saveFile(const char *fileName, const char *content) {
    char filePath[MAX_PATH];
    snprintf(filePath, sizeof(filePath), "uploads/%s", fileName);

    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    if (fwrite(content, strlen(content), 1, file) != 1) {
        perror("Failed to write content to the file");
    }

    fclose(file);
}

int main() {
    // Ensure the uploads directory exists
    system("mkdir -p uploads");

    const char *fileName = "example.txt";
    const char *content = "This is a sample text for the web app.";

    saveFile(fileName, content);

    printf("File saved successfully.\n");

    return 0;
}