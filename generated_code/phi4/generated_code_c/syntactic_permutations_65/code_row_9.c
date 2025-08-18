#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SERVER_URL "http://localhost/upload.php" // Assuming you have an upload script at this URL

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

int upload_file(const char *filepath) {
    CURL *curl;
    CURLcode res;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct MemoryStruct readbuffer;

    readbuffer.memory = malloc(1);
    readbuffer.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, "uploadfile",
                 CURLFORM_FILE, filepath,
                 CURLFORM_END);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, SERVER_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&readbuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_formfree(formpost);
        curl_easy_cleanup(curl);
    }

    free(readbuffer.memory);

    curl_global_cleanup();

    return 0;
}

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-pdf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filepath = argv[1];
    upload_file(filepath);

    return EXIT_SUCCESS;
}


This C code uses the libcurl library to perform an HTTP POST request to upload a PDF file to a web server. You need to have `libcurl` installed on your system and link it when compiling this program. The PHP script at `SERVER_URL` should handle the uploaded file and save it in the "uploads" folder.

To compile the code, you might use a command like:

gcc -o upload_program upload_program.c -lcurl


Make sure to replace `http://localhost/upload.php` with the actual URL of your web server's upload script. The PHP script should be prepared to handle file uploads and save them in the appropriate directory.