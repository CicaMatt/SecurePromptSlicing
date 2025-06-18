#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <curl/curl.h>

    void redirect_invalid_url(char* url) {
        CURL *curl;
        CURLcode res;
    
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
    
            if (res != CURLE_OK) {
                printf("Invalid URL\n");
            }
        }
    }