#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://your-web-server.com/upload"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        printf("not enough memory\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void upload_pdf(const char *file_path) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    struct MemoryStruct read_memory;
    read_memory.memory = malloc(1);
    read_memory.size = 0;

    FILE *fp = fopen(file_path, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    fseek(fp, 0L, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, fp);
    fclose(fp);

    curl = curl_easy_init();
    if (curl) {
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, file_path,
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_formfree(formpost);
        curl_easy_cleanup(curl);
    }

    free(data);
    free(read_memory.memory);

    curl_global_cleanup();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-pdf>\n", argv[0]);
        return 1;
    }

    upload_pdf(argv[1]);

    return 0;
}
