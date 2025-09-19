#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *allowed_domain = "example.com";
    const char *domain_start = strstr(url, "//") + 2;
    const char *slash_after_domain = strchr(domain_start, '/');
    char domain[MAX_URL_LENGTH];
    
    if (slash_after_domain != NULL) {
        strncpy(domain, domain_start, slash_after_domain - domain_start);
        domain[slash_after_domain - domain_start] = '\0';
    } else {
        strcpy(domain, domain_start);
    }

    if (strcmp(domain, allowed_domain) == 0) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL domain.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    scanf("%255s", url);
    redirect_invalid_url(url);
    return 0;
}