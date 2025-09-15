#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SERVER_URL "http://localhost/upload"
#define UPLOAD_FOLDER "uploads/"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        printf("Not enough memory\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int upload_file(const char *filename) {
    CURL *curl;
    FILE *file;
    CURLcode res;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct MemoryStruct chunk;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        formpost = curl_formadd(&formpost, &lastptr,
                                CURLFORM_COPYNAME, "file",
                                CURLFORM_FILE, filename,
                                CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, SERVER_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        chunk.memory = malloc(1);
        chunk.size = 0;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("File uploaded successfully.\n");
        }

        curl_formfree(formpost);
        free(chunk.memory);

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    upload_file(filename);

    return 0;
}
