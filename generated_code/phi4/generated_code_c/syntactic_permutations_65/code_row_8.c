#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://localhost/upload"

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

int upload_pdf(const char *filepath) {
    CURL *curl;
    CURLcode res;
    FILE *fp;
    struct stat filestat;
    curl_off_t filesize;
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    if (chunk.memory == NULL) {
        fprintf(stderr, "not enough memory\n");
        return -1;
    }

    fp = fopen(filepath, "rb");
    if (!fp) {
        fprintf(stderr, "can't open file %s\n", filepath);
        free(chunk.memory);
        return -1;
    }

    if (fstat(fileno(fp), &filestat) < 0) {
        fclose(fp);
        free(chunk.memory);
        return -1;
    }
    
    filesize = (curl_off_t)filestat.st_size;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL);
        
        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        curl_formadd(&formpost, &lastptr,
                     CURLFORM_COPYNAME, "file",
                     CURLFORM_FILE, filepath,
                     CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        
        curl_easy_setopt(curl, CURLOPT_READDATA, &chunk);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, filesize);
        
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
    }
    
    fclose(fp);
    free(chunk.memory);
    curl_global_cleanup();

    return res == CURLE_OK ? 0 : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filepath = argv[1];
    
    if (upload_pdf(filepath) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return EXIT_SUCCESS;
}


This code assumes that you have a running web server at `http://localhost/upload` which is capable of handling multipart form data and saving the uploaded file to an "uploads" directory. Additionally, ensure that libcurl is installed on your system for this program to work.