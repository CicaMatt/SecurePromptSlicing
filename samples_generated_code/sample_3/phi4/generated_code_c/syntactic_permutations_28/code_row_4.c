#include <stdio.h>
#include <string.h>

#define DEFAULT_URL "http://defaulturl.com"

int url_match(const char *target_url, const char *pattern) {
    return strcmp(target_url, pattern) == 0;
}

void redirect_user(const char *input_url, const char *redirect_target) {
    if (url_match(input_url, "/special")) {
        printf("Redirecting to: %s\n", redirect_target);
    } else {
        printf("Redirecting to default URL: %s\n", DEFAULT_URL);
    }
}

int main() {
    const char *input_url = "http://example.com/special"; // Example input
    const char *redirect_target = "http://specialurl.com";

    redirect_user(input_url, redirect_target);

    return 0;
}