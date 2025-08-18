#include <stdio.h>
#include <string.h>

const char* check_mod(const char *url) {
    const char *username = "admin";
    const char *password = "password123";

    if (strstr(url, "/check_mod?user=admin&pass=password123") != NULL) {
        return "true";
    }
    return "false";
}

int main() {
    const char *url1 = "/check_mod?user=admin&pass=password123";
    const char *url2 = "/check_mod?user=user&pass=wrong";

    printf("Check URL 1: %s\n", check_mod(url1)); // Should print true
    printf("Check URL 2: %s\n", check_mod(url2)); // Should print false

    return 0;
}