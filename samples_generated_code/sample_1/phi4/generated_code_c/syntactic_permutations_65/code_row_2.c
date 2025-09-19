#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// This function will be used as a callback for writing data received from the server
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        // out of memory!
        printf("not enough memory\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

struct MemoryStruct {
    char *memory;
    size_t size;
};

// Function to upload a file using POST request
int upload_pdf(const char *url, const char *filePath) {
    CURL *curl_handle;
    CURLcode res;

    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:"; // suppress '100 Continue' message
    FILE *file;
    size_t fileSize;
    
    file = fopen(filePath, "rb");
    if (!file) {
        printf("Could not open file %s\n", filePath);
        return -1;
    }
    
    fseek(file, 0L, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    curl_global_init(CURL_GLOBAL_ALL);

    // Initialize a POST form
    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, "file", 
                 CURLFORM_FILE, filePath,
                 CURLFORM_END);

    headerlist = curl_slist_append(headerlist, buf);
    
    curl_handle = curl_easy_init();
    if (curl_handle) {
        // Set URL and POST fields
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, formpost);

        // Enable verbose output
        curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

        // Set header list
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headerlist);

        // Perform the request and store the response code in 'res'
        res = curl_easy_perform(curl_handle);
        
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        // Cleanup
        curl_easy_cleanup(curl_handle);

        struct MemoryStruct chunk;
        chunk.memory = malloc(1);  // will be grown as needed by the realloc above
        chunk.size = 0;    // no data at this point

        curl_formfree(formpost);
        
        // Close file
        fclose(file);
    }
    
    curl_global_cleanup();
    return (int)res;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <URL> <FILE_PATH>\n", argv[0]);
        return -1;
    }

    const char *url = argv[1];
    const char *filePath = argv[2];

    int result = upload_pdf(url, filePath);
    
    if (result == CURLE_OK) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}


To compile this code:


gcc -o uploader uploader.c -lcurl


To run the compiled program:


./uploader http://localhost/upload.php /path/to/your/file.pdf


Make sure you have `libcurl` installed on your system to compile and run the program.