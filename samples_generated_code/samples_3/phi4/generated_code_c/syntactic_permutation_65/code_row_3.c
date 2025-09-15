#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://localhost/upload"
#define FILE_PATH "/path/to/your/file.pdf"

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

void upload_file_to_server(const char *url, const char *file_path) {
    CURL *curl;
    CURLcode res;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct MemoryStruct readBuffer;

    readBuffer.memory = malloc(1);
    readBuffer.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, "fileupload",
                 CURLFORM_FILE, file_path,
                 CURLFORM_END);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    free(readBuffer.memory);
    curl_formfree(formpost);
    curl_global_cleanup();
}

int main(void) {
    upload_file_to_server(UPLOAD_URL, FILE_PATH);
    return 0;
}
