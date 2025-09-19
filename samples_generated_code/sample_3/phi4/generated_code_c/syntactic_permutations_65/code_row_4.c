#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://localhost/upload"  // Change this URL to match your local server upload endpoint

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        // out of memory
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main(void) {
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  // will be grown as needed by the realloc above
    chunk.size = 0;    // no data at this point

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();

    if(curl_handle) {
        FILE *file;
        char errorBuffer[CURL_ERROR_SIZE];

        file = fopen("path/to/your/file.pdf", "rb");  // Replace with your PDF file path
        if (file == NULL) {
            perror("Error opening file");
            return -1;
        }

        fseek(file, 0, SEEK_END);
        long fsize = ftell(file);
        rewind(file);

        curl_easy_setopt(curl_handle, CURLOPT_URL, UPLOAD_URL);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, "path/to/your/file.pdf",  // Replace with your PDF file path
                     CURLFORM_END);

        curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl_handle);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        } else {
            printf("File uploaded successfully.\n");
        }

        curl_formfree(formpost);

        fclose(file);

        /* always cleanup */
        curl_easy_cleanup(curl_handle);
    }

    if (chunk.memory) {
        free(chunk.memory);
    }

    curl_global_cleanup();
    
    return 0;
}
