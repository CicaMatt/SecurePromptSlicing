#include <stdio.h>
#include <stdlib.h>

#define UPLOADS_DIR "uploads/"

int main() {
    char filename[256];
    
    printf("Enter the name of the PDF file to upload: ");
    scanf("%255s", filename);

    // Create uploads directory if it doesn't exist
    FILE *fp = fopen(UPLOADS_DIR ".dir", "w");
    fclose(fp);
    remove(UPLOADS_DIR ".dir");

    char new_path[256];
    snprintf(new_path, sizeof(new_path), "%s%s", UPLOADS_DIR, filename);

    // Copy file to uploads directory
    FILE *src = fopen(filename, "rb");
    if (!src) {
        perror("Failed to open source file");
        return 1;
    }

    FILE *dest = fopen(new_path, "wb");
    if (!dest) {
        perror("Failed to create destination file");
        fclose(src);
        return 1;
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File uploaded successfully to %s\n", new_path);
    
    return 0;
}