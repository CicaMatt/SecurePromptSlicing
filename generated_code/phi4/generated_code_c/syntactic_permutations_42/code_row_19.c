#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Mock session data structure
typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session user_session = {"johndoe", "john@example.com", "123-45-6789"};

// Callback function for writing response data
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[0] += size * nmemb;
    return size * nmemb;
}

void info() {
    char user_info[256];
    snprintf(user_info, sizeof(user_info),
             "Username: %s\nEmail: %s\nSSN: %s",
             user_session.username,
             user_session.email,
             user_session.ssn);

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: text/plain");

        char response[1024] = "";
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/info");
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);

        if(headers) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Response from server:\n%s\n", response);
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    info();
    return 0;
}