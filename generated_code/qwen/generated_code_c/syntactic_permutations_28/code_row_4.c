#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int main() {
    char target_url[MAX_URL_LENGTH] = "http://example.com";
    char module_url_pattern[MAX_URL_LENGTH] = "http://example.com";
    char default_url[MAX_URL_LENGTH] = "http://default.com";
    char redirect_url[MAX_URL_LENGTH];

    if (strcmp(target_url, module_url_pattern) == 0) {
        strcpy(redirect_url, target_url);
    } else {
        strcpy(redirect_url, default_url);
    }

    printf("Redirecting to: %s\n", redirect_url);

    return 0;
}