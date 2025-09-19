#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function declarations
int readFileToBase64(const char *filename, char **base64);
void insertImageInfo(const char *imageName, const char *imageBase64);

// Main function to simulate uploading an image
void upload_image(const char *filename) {
    char *base64 = NULL;
    
    if (readFileToBase64(filename, &base64)) {
        printf("Error reading file or converting to base64.\n");
        free(base64);
        return;
    }

    insertImageInfo(filename, base64);
    free(base64);
}

// Read the image file and convert it to a base64 string
int readFileToBase64(const char *filename, char **base64) {
    FILE *file = fopen(filename, "rb");
    if (!file) return -1;
    
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        fclose(file);
        return -2;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);

    // Calculate base64 length
    size_t base64Length = 4 * ((fileSize + 2) / 3);
    char *base64Str = (char *)malloc(base64Length + 1); // +1 for null terminator

    if (!base64Str) {
        free(buffer);
        return -3;
    }

    int i, j;
    for (i = 0, j = 0; i < fileSize;) {
        unsigned char octet_a = i < fileSize ? buffer[i++] : 0;
        unsigned char octet_b = i < fileSize ? buffer[i++] : 0;
        unsigned char octet_c = i < fileSize ? buffer[i++] : 0;

        unsigned int triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        unsigned char encoded1 = (triple >> 3 * 6) & 63;
        unsigned char encoded2 = (triple >> 2 * 6) & 63;
        unsigned char encoded3 = (triple >> 1 * 6) & 63;
        unsigned char encoded4 = (triple >> 0 * 6) & 63;

        switch (fileSize - i) {
            case 1:
                encoded3 = 64;
                encoded4 = 64;
                break;
            case 2:
                encoded4 = 64;
                break;
        }

        base64Str[j++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[encoded1];
        base64Str[j++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[encoded2];
        base64Str[j++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[encoded3];
        base64Str[j++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[encoded4];
    }

    base64Str[base64Length] = '\0';
    free(buffer);

    *base64 = base64Str;
    return 0;
}

// Insert image name and base64 string into a hypothetical storage system
void insertImageInfo(const char *imageName, const char *imageBase64) {
    // This is a placeholder for the actual database insertion logic.
    printf("Inserting Image Info:\n");
    printf("Name: %s\n", imageName);
    printf("Base64: %s\n", imageBase64);

    // Actual implementation would involve writing to a file or a database
}

int main() {
    const char *imageFilename = "example.jpg";
    upload_image(imageFilename);
    return 0;
}