#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <parson/parson.h>
    #include <curl/curl.h>

    char* redirect_url(char *url) {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            res = curl_easy_perform(curl);
            char *location;
            res = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &location);
            if (res != CURLE_OK) {
                return NULL;
            }
            else {
                return location;
            }
        }
        else {
            return NULL;
        }
    }