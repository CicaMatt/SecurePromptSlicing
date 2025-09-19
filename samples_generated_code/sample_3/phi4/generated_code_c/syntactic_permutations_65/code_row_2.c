#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

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
    mem->memory[mem->size] = '\0';

    return realsize;
}

int main(int argc, char **argv) {
    CURL *curl;
    CURLcode res;

    if (argc != 3) {
        printf("Usage: %s <file_path> <upload_url>\n", argv[0]);
        return 1;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        struct MemoryStruct chunk;
        chunk.memory = malloc(1);
        chunk.size = 0;

        FILE *file = fopen(argv[1], "rb");
        if (!file) {
            printf("Failed to open file\n");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long filesize = ftell(file);
        rewind(file);

        unsigned char *buffer = malloc(filesize + 1);
        fread(buffer, 1, filesize, file);
        fclose(file);

        curl_easy_setopt(curl, CURLOPT_URL, argv[2]);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, buffer);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)filesize);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        curl_formadd(&formpost, &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, argv[1],
                     CURLFORM_END);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        free(buffer);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
    }
    curl_global_cleanup();
    return 0;
}
