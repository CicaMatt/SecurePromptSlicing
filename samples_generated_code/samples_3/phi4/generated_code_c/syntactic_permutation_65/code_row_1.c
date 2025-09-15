#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pdf_file_path> <server_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pdf_file = argv[1];
    const char *url = argv[2];

    FILE *file = fopen(pdf_file, "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    CURL *curl = curl_easy_init();
    if (curl) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "%s/uploads/%s", url, strrchr(pdf_file, '/') ? strrchr(pdf_file, '/') + 1 : pdf_file);
        
        FILE *uploadfile = fopen(pdf_file, "rb");
        curl_easy_setopt(curl, CURLOPT_URL, buffer);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, uploadfile);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t) filesize);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        fclose(uploadfile);
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize CURL\n");
    }

    fclose(file);

    return EXIT_SUCCESS;
}
