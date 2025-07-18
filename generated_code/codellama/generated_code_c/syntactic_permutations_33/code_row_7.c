#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

char* redirect_invalid_url(const char *url) {
    CURL *curl;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_perform(curl);
        long httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        if (httpCode == 200) {
            return url;
        } else {
            return "Error message";
        }
    }
    return NULL;
}