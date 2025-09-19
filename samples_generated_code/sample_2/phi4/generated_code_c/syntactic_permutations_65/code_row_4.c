#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_URL "http://localhost/upload"
#define UPLOAD_DIR "./uploads/"
#define BUFFER_SIZE 1024

void handle_file_upload(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Initialize CURL
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        struct curl_slist *headerlist = NULL;

        // Add file to form
        curl_formadd(&formpost, &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, file_path,
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, SERVER_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_formfree(formpost);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    const char *upload_dir = UPLOAD_DIR;

    // Ensure the upload directory exists
    mkdir(upload_dir, 0777);

    char full_upload_path[BUFFER_SIZE];
    snprintf(full_upload_path, BUFFER_SIZE, "%s%s", upload_dir, strrchr(file_path, '/') ? strrchr(file_path, '/') + 1 : file_path);
    
    // Copy the PDF to the local uploads directory
    FILE *src = fopen(file_path, "rb");
    if (!src) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    FILE *dest = fopen(full_upload_path, "wb");
    if (!dest) {
        fclose(src);
        perror("Failed to open destination file");
        return EXIT_FAILURE;
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(src);
    fclose(dest);

    // Upload the PDF to the server
    handle_file_upload(full_upload_path);

    return EXIT_SUCCESS;
}
