#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Structure for handling memory allocation during file download
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function to handle data received from the server
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        // out of memory!
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// Function to upload a file using cURL
int upload_file(const char *file_path) {
    CURL *curl;
    CURLcode res;

    // Initialize a memory structure for the response data
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        curl_mime *form = NULL;
        curl_mimepart *field = NULL;

        form = curl_mime_init(curl);

        // Create a file field in the multipart/form-data
        field = curl_mime_addpart(form);
        curl_mime_name(field, "file");
        curl_mime_filedata(field, file_path);

        // Set up the cURL options for POST request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/upload");
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_mime_free(form);
        curl_easy_cleanup(curl);

        free(chunk.memory);

    } else {
        fprintf(stderr, "Error initializing cURL\n");
        return 1;
    }
    
    curl_global_cleanup();
    return 0;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    
    // Upload the file
    int result = upload_file(file_path);
    if(result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }
    
    return result;
}
