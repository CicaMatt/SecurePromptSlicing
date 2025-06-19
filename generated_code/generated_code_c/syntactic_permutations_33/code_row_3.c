#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "http_redirect.h"
void redirect_invalid_url(char *url);
int main() {
    char url[1024];
    printf("Enter the URL: ");
    fgets(url, 1024, stdin);
    redirect_invalid_url(url);
    return 0;
}
void redirect_invalid_url(char *url) {
    char *domain = "example.com";
    int len = strlen(domain);
    if (strncmp(domain, url, len) == 0) {
        printf("URL is valid\n");
        http_redirect(url);
    } else {
        printf("Invalid URL\n");
    }
}