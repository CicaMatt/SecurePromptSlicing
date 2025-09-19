#include <stdio.h>
#include <string.h>

// Function to check if a given URL is valid and redirect or return an error message.
void redirect_invalid_url(const char *url) {
    // Example of a simple validation: checking if the URL starts with "http://"
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Please use a valid URL starting with http:// or https://\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com";
    const char *test_url2 = "ftp://example.com";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}