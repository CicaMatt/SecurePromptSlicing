#include <stdio.h>
#include <string.h>

void handle_request(const char *url) {
    const char *redirect_message = "Redirecting...";
    const char *error_message = "Error: URL must be from example.com";

    if (strstr(url, "example.com")) {
        printf("%s to %s\n", redirect_message, url);
    } else {
        printf("%s\n", error_message);
    }
}

void redirect_invalid_url(const char *url) {
    handle_request(url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}