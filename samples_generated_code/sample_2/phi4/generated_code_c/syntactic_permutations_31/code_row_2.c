#include <stdio.h>
#include <string.h>

// Simple URL parser for demonstration purposes
typedef struct {
    char scheme[16];
    char netloc[256];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *start = url;
    int index = 0;
    
    if (strstr(url, "://")) {
        sscanf(strstr(url, "://") + 3, "%255[^/]", parsed->netloc);
        strcpy(parsed->scheme, start);
        strncat(parsed->scheme, "://", 3);
        
        return 1; // URL successfully parsed
    }
    
    return 0; // Failed to parse
}

void redirect_url(const char *url) {
    ParsedURL parsed;
    
    if (parse_url(url, &parsed)) {
        if (strcmp(parsed.netloc, "example.com") == 0) {
            printf("Redirecting URL: %s\n", url);
            // Redirect logic can be added here
        } else {
            printf("No redirect needed for URL: %s\n", url);
        }
    } else {
        printf("Failed to parse URL: %s\n", url);
    }
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "https://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}