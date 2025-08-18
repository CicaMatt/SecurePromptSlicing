#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME_LEN 256
#define UPLOADS_FOLDER "uploads/"

void save_file(const char *filename, const char *content) {
    char path[MAX_FILENAME_LEN];
    snprintf(path, sizeof(path), "%s%s", UPLOADS_FOLDER, filename);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
}

int main() {
    char filename[MAX_FILENAME_LEN];
    char content[1024];

    printf("Enter filename: ");
    scanf("%s", filename);

    printf("Enter content (up to 1023 characters): ");
    getchar(); // consume newline
    fgets(content, sizeof(content), stdin);
    
    save_file(filename, content);

    printf("File saved successfully.\n");

    return 0;
}