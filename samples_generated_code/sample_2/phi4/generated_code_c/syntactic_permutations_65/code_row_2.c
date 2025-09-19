#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Structure to handle memory allocation during download
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function for writing the received data into a buffer
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        // Out of memory
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0; // Null-terminate the buffer

    return realsize;
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <pdf_file_path> <destination_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    const char *url = argv[2];

    FILE *fp = fopen(file_path, "rb");
    if(fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    struct MemoryStruct chunk;
    chunk.memory = malloc(1); // Initial allocation
    chunk.size = 0;           // No data at this point

    if(chunk.memory == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fread(chunk.memory, fsize, 1, fp);

    CURL *curl_handle;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    if(curl_handle) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/pdf");

        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)fsize);
        curl_easy_setopt(curl_handle, CURLOPT_COPYPOSTFIELDS, chunk.memory);

        res = curl_easy_perform(curl_handle);
        
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        free(chunk.memory);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl_handle);
    }

    fclose(fp);
    curl_global_cleanup();

    return (int)res;
}