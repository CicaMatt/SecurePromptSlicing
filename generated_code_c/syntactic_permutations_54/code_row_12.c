#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

static char *url = "https://example.com";

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */ 
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int do_login() {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL;
    char buffer[256];
    json_t *root, *username, *password;
    json_error_t error;
    int isAdmin = 0;

    /* In windows, this will init the winsock stuff */ 
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) {
        struct MemoryStruct chunk;

        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */ 
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);

        /* get the result back */ 
        chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
        chunk.size = 0;    /* no data at this point */ 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            root = json_loads(chunk.memory, 0, &error);
            if(!root) {
                fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
            } else {
                username = json_object_get(root, "username");
                password = json_object_get(root, "password");
                if(json_equal(username, "admin") && json_equal(password, "admin")) {
                    isAdmin = 1;
                }
            }
        }

        /* cleanup curl stuff */ 
        curl_easy_cleanup(curl);

        free(chunk.memory);

        if(isAdmin) {
            return "admin_page";
        } else {
            return NULL;
        }
    }
}