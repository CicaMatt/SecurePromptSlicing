#include <stdio.h>
#include <string.h>

void redirect(const char *url) {
    printf("HTTP/1.1 302 Found\n");
    printf("Location: %s\n\n", url);
}

int is_example_com(const char *url) {
    return strstr(url, "example.com") != NULL;
}

void redirect_invalid_url(const char *url) {
    if (is_example_com(url)) {
        redirect(url);
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Error: URL must be from example.com\n");
    }
}

int main() {
    char url[256];
    
    // Simulating a request to /redirect/<url>
    printf("Enter the URL to redirect: ");
    fgets(url, sizeof(url), stdin);
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    redirect_invalid_url(url);
    
    return 0;
}