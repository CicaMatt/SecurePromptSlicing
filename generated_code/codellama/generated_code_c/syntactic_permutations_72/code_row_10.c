#include <stdio.h> 
#include <string.h> 
#include "stdlib.h" 
#include "upload_file.h" 

int main() { 
    char *filename = "/path/to/myfile.txt"; 
    upload_file(filename); 
} 

void upload_file(char *filename) { 
    // Open the file in binary mode 
    FILE *pFile; 
    pFile = fopen(filename, "rb"); 

    // Get the file size 
    fseek(pFile, 0, SEEK_END); 
    long lSize = ftell(pFile); 
    rewind(pFile); 

    // Read the data and store in buffer 
    char *buffer = (char *)malloc(sizeof(char) * lSize); 
    fread(buffer, 1, lSize, pFile); 

    // Close the file 
    fclose(pFile); 

    // Upload the data to the server using HTTP POST 
    CURL *curl; 
    curl_global_init(CURL_GLOBAL_ALL); 
    curl = curl_easy_init(); 

    struct curl_slist *headers = NULL; 
    headers = curl_slist_append(headers, "Content-Type:application/octet-stream"); 
    headers = curl_slist_append(headers, "Expect:"); 

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com/upload"); 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer); 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, lSize); 

    CURLcode res = curl_easy_perform(curl); 

    if (res != CURLE_OK) { 
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); 
    } else { 
        printf("File uploaded successfully."); 
    } 

    // Clean up 
    free(buffer); 
    curl_easy_cleanup(curl); 
    curl_slist_free_all(headers); 
}