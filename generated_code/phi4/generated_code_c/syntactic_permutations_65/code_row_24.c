#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

void upload_pdf(const char *filename) {
    CURL *curl;
    CURLcode res;
    FILE *file;

    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    curl = curl_easy_init();
    if (curl) {
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        struct curl_slist *headerlist = NULL;

        curl_formadd(&formpost, &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, filename,
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/upload");
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_formfree(formpost);
        curl_easy_cleanup(curl);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_pdf(argv[1]);

    return EXIT_SUCCESS;
}


To compile and run this code:


gcc -o upload pdf_uploader.c -lcurl
./upload path/to/your/file.pdf


Ensure that `libcurl` is installed on your system. You can install it using a package manager like `apt`, `yum`, or `brew`.