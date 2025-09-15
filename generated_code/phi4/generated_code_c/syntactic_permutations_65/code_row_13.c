#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SERVER_URL "http://localhost/upload"
#define UPLOAD_DIR "/path/to/your/uploads/directory"  // Update this path

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        fprintf(stderr, "Not enough memory\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int upload_file(const char *filename) {
    CURL *curl_handle;
    CURLcode res;
    FILE *file;
    struct MemoryStruct chunk;

    file = fopen(filename, "rb");
    if(file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return -1;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    if(curl_handle) {
        chunk.memory = malloc(1);
        chunk.size = 0;

        curl_easy_setopt(curl_handle, CURLOPT_URL, SERVER_URL);
        curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_READDATA, file);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, filename,
                     CURLFORM_END);

        curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl_handle);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_formfree(formpost);
        curl_easy_cleanup(curl_handle);
    }

    fclose(file);
    free(chunk.memory);
    curl_global_cleanup();

    return (res == CURLE_OK) ? 0 : -1;
}

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *upload_path = malloc(strlen(UPLOAD_DIR) + strlen(filename) + 2);
    sprintf(upload_path, "%s/%s", UPLOAD_DIR, filename);

    if(rename(filename, upload_path) != 0) {
        fprintf(stderr, "Error moving file to uploads directory\n");
        return 1;
    }

    if(upload_file(upload_path) == 0) {
        printf("File uploaded successfully\n");
    } else {
        fprintf(stderr, "Failed to upload file\n");
    }

    free(upload_path);
    return 0;
}
