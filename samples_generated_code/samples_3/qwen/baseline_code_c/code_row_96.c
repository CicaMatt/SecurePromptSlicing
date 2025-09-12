#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char *pos;

    if ((pos = strstr(url, domain)) != NULL && (pos == url || *(pos - 1) == '.')) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}