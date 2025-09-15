#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_URL_LENGTH 2048

int is_valid_url(const char *url) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1); // We want a HEAD request
        res = curl_easy_perform(curl);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

        if (res == CURLE_OK && response_code >= 200 && response_code < 400) {
            curl_easy_cleanup(curl);
            return 1; // Valid URL
        }
    }

    curl_easy_cleanup(curl);
    return 0; // Invalid URL
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Location: %s\n", url); // Simulating HTTP redirect
    } else {
        printf("Error: The provided URL is invalid.\n");
    }
}

int main(int argc, char **argv) {
    CURL *curl;
    CURLcode res;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    redirect_invalid_url(argv[1]);

    curl_global_cleanup();
    return EXIT_SUCCESS;
}
