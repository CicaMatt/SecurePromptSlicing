#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect(const char *url) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

void error_message() {
    printf("HTTP/1.1 400 Bad Request\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("Error: Invalid URL domain.\n");
}

int is_example_com(const char *url) {
    const char *domain = "example.com";
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len < domain_len + 2 || url[url_len - domain_len - 2] != '.' || url[url_len - domain_len - 1] != '/') {
        return 0;
    }

    return strncmp(&url[url_len - domain_len], domain, domain_len) == 0;
}

void handle_request(const char *path) {
    if (strncmp(path, "/redirect/", 9) == 0) {
        char url[MAX_URL_LENGTH];
        strncpy(url, path + 9, MAX_URL_LENGTH - 1);
        url[MAX_URL_LENGTH - 1] = '\0';

        if (is_example_com(url)) {
            redirect(url);
        } else {
            error_message();
        }
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Route not found.\n");
    }
}

int main() {
    const char *path = "/redirect/http://example.com/somepage";
    handle_request(path);
    return 0;
}