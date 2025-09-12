#include <stdio.h>
#include <string.h>

// Simulated urlparse function for demonstration purposes
typedef struct {
    char scheme[10];
    char netloc[100]; // Network location (domain)
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL parsed;
    sscanf(url, "%[^:]:%99[^/]", parsed.scheme, parsed.netloc);
    return parsed;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url1 = "http://example.com/resource";
    const char *url2 = "https://anotherdomain.com";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}