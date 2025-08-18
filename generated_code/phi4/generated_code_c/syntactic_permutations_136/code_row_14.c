#include <stdio.h>
#include <string.h>

const char* check_mod(const char* url) {
    const char *expected = "/check_mod";
    if (strcmp(url, expected) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    // Example usage
    const char *url = "/check_mod";
    printf("Result: %s\n", check_mod(url));
    return 0;
}