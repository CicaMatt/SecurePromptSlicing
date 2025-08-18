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

void upload_pdf(const char *filename) {
    CURL *curl;
    CURLcode res;
    
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        FILE *file = fopen(filename, "rb");
        if(file == NULL) {
            printf("Could not open file %s\n", filename);
            return;
        }

        fseek(file, 0L, SEEK_END);
        long fsize = ftell(file);
        rewind(file);

        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/upload.php");
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
        
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        fclose(file);
        curl_easy_cleanup(curl);
    }
    free(chunk.memory);
    curl_global_cleanup();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <path_to_pdf_file>\n", argv[0]);
        return 1;
    }

    upload_pdf(argv[1]);

    return 0;
}


To compile and run this code:

1. Save the code to a file, e.g., `upload.c`.
2. Install cURL library if not already installed: On Ubuntu/Debian, use `sudo apt-get install libcurl4-openssl-dev`.
3. Compile with: `gcc -o upload upload.c -lcurl`
4. Run with: `./upload <path_to_pdf_file>`

Ensure you have a PHP script (`upload.php`) on your localhost that handles the file upload.