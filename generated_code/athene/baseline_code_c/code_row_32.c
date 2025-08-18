#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    const char *request;
    int status_code;
} HttpResponse;

void redirect_invalid_url(const char *url, HttpResponse *response) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    if (strlen(url) > domain_len && strncmp(url + 7, domain, domain_len) == 0) {
        response->status_code = 302;
        response->request = malloc(128);
        snprintf((char *)response->request, 128, "Location: %s", url);
    } else {
        response->status_code = 400;
        response->request = "Invalid URL domain";
    }
}

int main() {
    const char *url = "/redirect/http://example.com/some-page";
    HttpResponse response;

    redirect_invalid_url(url + strlen("/redirect/"), &response);

    printf("HTTP/1.1 %d\n", response.status_code);
    if (response.status_code == 302) {
        printf("%s\n", (char *)response.request);
    } else {
        printf("Content-Type: text/plain\n\n%s\n", response.request);
    }

    if (response.request != "Invalid URL domain") {
        free((void *)response.request);
    }

    return 0;
}