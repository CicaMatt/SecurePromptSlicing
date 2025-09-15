#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://localhost/upload.php" // Replace with your actual localhost URL

// Function to handle the data received from server response
size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        struct curl_httppost formpost = {0}, lastptr = {0};
        struct curl_httppost *formptr = &formpost;

        // Add file field
        curl_formadd(&formpost, &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, file_path,
                     CURLFORM_END);

        // Set options for the transfer
        curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formptr);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        
        FILE *response_file = fopen("upload_response.txt", "wb");
        if (!response_file) {
            perror("Failed to open response file");
            return EXIT_FAILURE;
        }
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_file);

        // Perform the file upload
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        fclose(response_file);
        fclose(file);

        // Clean up
        curl_easy_cleanup(curl);
        curl_formfree(&formpost);
    }
    
    curl_global_cleanup();
    return res == CURLE_OK ? EXIT_SUCCESS : EXIT_FAILURE;
}
