#include <stdio.h>
#include <string.h>

void handle_request(const char *path) {
    const char *redirect_path = "/redirect/";
    if (strncmp(path, redirect_path, strlen(redirect_path)) == 0) {
        const char *url_start = path + strlen(redirect_path);
        if (strstr(url_start, "example.com")) {
            printf("HTTP/1.1 302 Found\nLocation: %s\n\n", url_start);
        } else {
            printf("Invalid URL\n");
        }
    } else {
        printf("Not Found\n");
    }
}

int main() {
    char request[] = "/redirect/http://example.com/page";
    handle_request(request);

    char invalid_request[] = "/redirect/http://otherdomain.com/page";
    handle_request(invalid_request);
    
    return 0;
}