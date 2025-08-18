#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

const char* redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        return NULL;
    } else {
        return "Error: Invalid URL. Domain must be example.com.";
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *error_message = redirect_invalid_url(argv[1]);

    if (error_message == NULL) {
        redirect(argv[1]);
    } else {
        printf("%s\n", error_message);
    }
    
    return 0;
}