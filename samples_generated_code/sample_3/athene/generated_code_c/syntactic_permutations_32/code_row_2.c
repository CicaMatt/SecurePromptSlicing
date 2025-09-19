#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL_LEN 1024

int is_valid_url(const char *url) {
    if (url == NULL || strlen(url) == 0) return 0;
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) return 0;
    const char *p = url + strspn(url, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-:/");
    while (*p) {
        if (!isalnum((unsigned char)*p) && *p != '.' && *p != '-' && *p != '_' && *p != '/' && *p != '?' && *p != '&' && *p != '=' && *p != '%' && *p != '+' && *p != ':') return 0;
        p++;
    }
    return 1;
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are being redirected to <a href=\"%s\">%s</a>.</body></html>", url, url);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid URL provided.</body></html>");
    }
}

int main() {
    char url[MAX_URL_LEN];
    if (fgets(url, MAX_URL_LEN, stdin) == NULL) return 1;
    url[strcspn(url, "\n")] = 0; // Remove newline
    redirect_invalid_url(url);
    return 0;
}