#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 1024

void handle_errors(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

char* read_file_to_string(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file)
        handle_errors("Error opening file");

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char *content = (char*)malloc(size + 1);
    if (!content)
        handle_errors("Memory allocation failed");

    fread(content, 1, size, file);
    content[size] = '\0';
    
    fclose(file);
    return content;
}

int write_to_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "w");
    if (!file)
        handle_errors("Error opening file");

    fprintf(file, "%s", data);
    fclose(file);

    return 0;
}

char* convert_image_to_base64(const unsigned char *image_data, size_t image_size) {
    BIO *bio_mem, *bio_b64;
    BUF_MEM *bufferPtr;

    bio_mem = BIO_new(BIO_s_mem());
    if (!bio_mem)
        handle_errors("BIO_new() failed");

    bio_b64 = BIO_new(BIO_f_base64());
    if (!bio_b64) {
        BIO_free_all(bio_mem);
        handle_errors("BIO_new() for base64 failed");
    }

    bio_mem = BIO_push(bio_b64, bio_mem);

    BIO_write(bio_mem, image_data, image_size);
    BIO_flush(bio_mem);
    BIO_get_mem_ptr(bio_mem, &bufferPtr);
    BIO_set_close(bio_mem, BIO_NOCLOSE);

    char *base64_image = (char *)malloc(bufferPtr->length + 1);
    if (!base64_image)
        handle_errors("Memory allocation failed");

    memcpy(base64_image, bufferPtr->data, bufferPtr->length);
    base64_image[bufferPtr->length] = '\0';

    BIO_free_all(bio_mem);

    return base64_image;
}

void upload_image(const char *image_path) {
    char *file_content = read_file_to_string(image_path);
    if (!file_content)
        handle_errors("Failed to read file");

    size_t image_size = strlen(file_content);
    char *base64_image = convert_image_to_base64((unsigned char*)file_content, image_size);

    // Insert the base64 string and filename into a database or a text file
    const char *db_insert_path = "image_data.txt";
    
    FILE *db_file = fopen(db_insert_path, "a");
    if (!db_file)
        handle_errors("Error opening database file");

    fprintf(db_file, "Image Name: %s\nBase64 String:\n%s\n", strrchr(image_path, '/') + 1, base64_image);
    fclose(db_file);

    free(file_content);
    free(base64_image);
}

int main() {
#ifdef _WIN32
    SetConsoleTitleA("Upload Image Example");
#endif

    const char *image_path = "sample.jpg"; // Path to your image file
    upload_image(image_path);

    printf("Image uploaded successfully.\n");

    return 0;
}
