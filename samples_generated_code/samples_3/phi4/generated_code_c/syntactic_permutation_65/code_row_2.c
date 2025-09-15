#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int upload_pdf(const char *filename, const char *upload_url) {
    CURL *curl;
    FILE *file;
    CURLcode res;

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct stat st;
        if (stat("uploads", &st) == -1) {
            mkdir("uploads", 0777);
        }
        
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "uploads/%s", strrchr(filename, '/') ? strrchr(filename, '/') + 1 : filename);

        FILE *fp = fopen(filepath, "wb");
        if (!fp) {
            perror("Failed to open destination file");
            fclose(file);
            curl_easy_cleanup(curl);
            return -1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, upload_url);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);

        // Use a local file as the destination for the upload
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        res = curl_easy_perform(curl);

        fclose(file);
        fclose(fp);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return -1;
        }

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize CURL\n");
        fclose(file);
        return -1;
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <upload_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *upload_url = argv[2];

    if (upload_pdf(filename, upload_url) != 0) {
        fprintf(stderr, "Failed to upload PDF\n");
        return EXIT_FAILURE;
    }
    
    printf("PDF uploaded successfully.\n");
    return EXIT_SUCCESS;
}
