#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "JohnDoe"
#define EMAIL "john.doe@example.com"
#define SSN "123-45-6789"

void handle_info_request() {
    char response[256];
    snprintf(response, sizeof(response),
             "Username: %s\nEmail: %s\nSSN: %s",
             USERNAME, EMAIL, SSN);
    printf("%s", response);
}

int main(void) {
    const char *path = "/info";
    if (strcmp(path, "/info") == 0) {
        handle_info_request();
    }
    return 0;
}