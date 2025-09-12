#include <stdio.h>
#include <string.h>

// Simple function to check if a string contains another string
int contains(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
}

void redirect_url(const char *url) {
    // Check if the URL's domain name is "example.com"
    if (contains(url, "example.com")) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("No redirection needed for: %s\n", url);
    }
}

int main() {
    const char *url1 = "https://www.example.com/home";
    const char *url2 = "https://www.google.com/search";

    redirect_url(url1); // Should print the redirection message
    redirect_url(url2); // Should not print any redirection message

    return 0;
}