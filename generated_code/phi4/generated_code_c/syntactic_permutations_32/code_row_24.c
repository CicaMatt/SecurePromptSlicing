#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *base_url = "example.com";
    
    if (strstr(url, base_url)) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: %s\n", url);
        printf("\n"); // End of headers
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: URL is not from example.com.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}