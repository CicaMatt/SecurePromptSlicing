#include <stdio.h>
#include <string.h>

FILE* img(const char* name) {
    char path[100];
    snprintf(path, sizeof(path), "images/%s", name);
    return fopen(path, "rb");
}

int main() {
    const char* imageName = "example.jpg";
    FILE* imageFile = img(imageName);

    if (imageFile == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fclose(imageFile);
    return 0;
}