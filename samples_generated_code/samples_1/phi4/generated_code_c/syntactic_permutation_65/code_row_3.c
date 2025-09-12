#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realSize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realSize + 1);
    if(ptr == NULL) {
        printf("Not enough memory\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realSize);
    mem->size += realSize;
    mem->memory[mem->size] = 0;

    return realSize;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <URL> <PDF file path>\n", argv[0]);
        return 1;
    }

    CURL *curl_handle;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();

    if(curl_handle) {
        FILE *file = fopen(argv[2], "rb");
        if (file == NULL) {
            printf("Could not open file %s\n", argv[2]);
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fsize = ftell(file);
        rewind(file);

        char *buffer = malloc(fsize + 1);
        fread(buffer, 1, fsize, file);
        fclose(file);
        buffer[fsize] = '\0';

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/pdf");
        headers = curl_slist_append(headers, "Content-Disposition: form-data; filename=\"file.pdf\"");

        curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_READDATA, buffer);
        curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);

        res = curl_easy_perform(curl_handle);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl_handle);
        free(buffer);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();

    return 0;
}


To compile and run the program:
1. Install libcurl development package if not already installed.
2. Compile with: `gcc -o upload_pdf upload.c $(pkg-config --cflags --libs libcurl)`
3. Run with: `./upload_pdf <URL> <PDF file path>`