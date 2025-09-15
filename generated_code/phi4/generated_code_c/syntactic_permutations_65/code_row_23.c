#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://your-web-server-address/upload"
#define UPLOAD_DIR "/path/to/your/uploads/folder"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        fprintf(stderr, "Not enough memory\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int upload_file(const char *filename) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct readMemory;
    FILE *file;
    
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        file = fopen(filename, "rb");
        if (!file) {
            fprintf(stderr, "File not found\n");
            return 1;
        }

        fseek(file, 0L, SEEK_END);
        long filesize = ftell(file);
        rewind(file);

        curl_mime *form = NULL;
        curl_mimepart *field = NULL;

        form = curl_mime_init(curl);
        field = curl_mime_addpart(form);

        curl_mime_name(field, "file");
        curl_mime_filedata(field, filename);

        curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL);
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
        
        readMemory.memory = malloc(1);
        readMemory.size = 0;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&readMemory);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Upload successful\n");
        }

        curl_mime_free(form);
        fclose(file);
        free(readMemory.memory);

        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf-file-path>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    
    // Ensure the uploads directory exists
    mkdir(UPLOAD_DIR, 0755); // This is a simple approach; more robust methods could be used for production

    upload_file(filename);
    return 0;
}
