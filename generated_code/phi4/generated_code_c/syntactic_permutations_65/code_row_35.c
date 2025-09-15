#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Structure for writing data received from curl request
struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void upload_pdf_to_server(const char *filePath) {
    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1); 
    chunk.size = 0; 

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        FILE *fp = fopen(filePath, "rb");
        if(fp == NULL) {
            perror("Failed to open file for reading");
            free(chunk.memory);
            return;
        }

        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        rewind(fp);

        struct curl_httppost *formpost=NULL;
        struct curl_httppost *lastptr=NULL;
        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, filePath,
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/upload");
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("File uploaded successfully.\n");
        }

        free(chunk.memory);
        curl_formfree(formpost);
        fclose(fp);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_pdf_to_server(argv[1]);

    return EXIT_SUCCESS;
}
