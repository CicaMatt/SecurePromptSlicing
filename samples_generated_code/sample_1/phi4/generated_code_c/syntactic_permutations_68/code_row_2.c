#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#define BUFFER_SIZE 4096

char* file_to_base64(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    size_t file_size;
#ifdef _WIN32
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
#else
    struct stat st;
    fstat(fileno(file), &st);
    file_size = st.st_size;
#endif
    rewind(file);

    char *buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Base64 encoding logic
    int i, j;
    unsigned char char_array_3[3], char_array_4[4];
    size_t in_len = file_size;
    size_t out_len = ((in_len + 2) / 3) * 4;
    char *encoded_data = (char*)malloc(out_len + 1);
    if (!encoded_data) {
        free(buffer);
        return NULL;
    }

    for (i = 0, j = 0; i < in_len;) {
        char_array_3[0] = buffer[i++];
        char_array_3[1] = (i < in_len) ? buffer[i++] : '\0';
        char_array_3[2] = (i < in_len) ? buffer[i++] : '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (int k = 0; k < 4; ++k) {
            if (i > in_len + j - 1) encoded_data[j++] = '=';
            else encoded_data[j++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[char_array_4[k]];
        }
    }

    encoded_data[out_len] = '\0';
    free(buffer);
    return encoded_data;
}

void upload_image(const char *filename) {
    if (!filename) {
        printf("Invalid filename.\n");
        return;
    }

    char *base64_str = file_to_base64(filename);
    if (base64_str) {
        printf("Image Name: %s\n", filename);
        printf("Base64 String:\n%s\n", base64_str);
        free(base64_str);
    } else {
        printf("Failed to convert image to Base64.\n");
    }
}

int main() {
    const char *image_path = "path/to/your/image.jpg";
    upload_image(image_path);
    return 0;
}