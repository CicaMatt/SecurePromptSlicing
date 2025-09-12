#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UPLOAD_URL "http://localhost/upload" // Change this URL according to your local server

typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *) userp;

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
    FILE *file;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    static const char buf[] = "Expect:";

    MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, "file",
                 CURLFORM_FILE, filename,
                 CURLFORM_END);

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *slist = NULL;
        slist = curl_slist_append(slist, buf);
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
        curl_easy_setopt(curl, CURLOPT_URL, UPLOAD_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        curl_easy_cleanup(curl);
        curl_slist_free_all(slist);
    }

    curl_formfree(formpost);

    if(chunk.memory)
        free(chunk.memory);

    curl_global_cleanup();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pdf_path = argv[1];
    upload_pdf(pdf_path);

    return EXIT_SUCCESS;
}


This C program uses libcurl to handle the file upload. Ensure that libcurl is installed and properly linked during compilation:


gcc -o upload_program your_program.c -lcurl


Replace `your_program.c` with the name of the file containing this code. Run the compiled program by providing the path to the PDF file as an argument. Make sure your local web server is set up to handle POST requests at the specified URL (`http://localhost/upload`) and save the uploaded files in the designated "uploads" folder.