#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    char buffer[MAX_URL_LENGTH];
    strncpy(buffer, url, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *host_start = strstr(buffer, "://");
    if (host_start == NULL) return 0;
    host_start += 3;

    char *path_start = strchr(host_start, '/');
    if (path_start != NULL) {
        *path_start = '\0';
    }

    return strcmp(host_start, domain) == 0;
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        exit(0);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Content-Type: text/plain\n\n");
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}