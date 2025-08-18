#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://localhost/uploads"
#define BUFFER_SIZE 1024

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp) {
    FILE *fp = (FILE *)userp;
    size_t fread_amount;

    if (size * nmemb < 1) {
        return 0;
    }

    fread_amount = fread(ptr, size, nmemb, fp);
    return fread_amount;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    CURL *curl;
    FILE *fd;
    struct stat file_info;
    curl_off_t fsize;

    fd = fopen(argv[1], "rb");
    if (!fd) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (fstat(fileno(fd), &file_info)) {
        fprintf(stderr, "Error getting file size\n");
        fclose(fd);
        return EXIT_FAILURE;
    }
    fsize = (curl_off_t)file_info.st_size;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: multipart/form-data");

        curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, fd);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "upload",
                     CURLFORM_FILE, argv[1],
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_formfree(formpost);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    fclose(fd);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}