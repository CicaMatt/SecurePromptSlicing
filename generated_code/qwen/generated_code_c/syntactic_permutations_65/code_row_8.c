#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://localhost/uploads"
#define MAX_FILENAME_LENGTH 256

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        printf("not enough memory (realloc returned NULL)\n");
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
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  
    chunk.size = 0;       

    FILE *fd = fopen(filename, "rb");
    if (!fd) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        struct stat file_info;
        fstat(fileno(fd), &file_info);
        
        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "sendfile",
                     CURLFORM_FILE, filename,
                     CURLFORM_CONTENTTYPE, "application/pdf",
                     CURLFORM_END);

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "filename",
                     CURLFORM_COPYCONTENTS, filename,
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
    fclose(fd);
    curl_global_cleanup();

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file-path>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int result = upload_file(filename);

    free(chunk.memory);
    return result;
}