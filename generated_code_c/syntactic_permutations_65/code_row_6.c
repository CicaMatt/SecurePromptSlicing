//include libraries needed for HTTP requests
#include <curl/curl.h>
#include <string.h>

int main(void) {
    //initiate the curl session
    CURL *curl;
    CURLcode res;
    
    //set the url to send the file to
    char url[256] = "localhost:8080/uploads";

    //open a file dialog and select the pdf file to upload
    FILE *file_to_send;
    fopen(file_to_send, "path/to/pdf", "r");
    
    //set up the http headers for the request
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "content-type: application/pdf");
    
    //initiate the upload request and set parameters
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, file_to_send);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }
    
    //perform the upload request
    res = curl_easy_perform(curl);
    
    //check for errors and display message if any
    if (res != CURLE_OK){
        fprintf(stderr, "failed to send the file\n");
    } else {
        printf("file successfully uploaded\n");
    }
    
    //close curl session and free memory
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
}