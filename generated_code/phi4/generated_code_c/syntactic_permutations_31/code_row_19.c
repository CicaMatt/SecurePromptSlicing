#include <stdio.h>
#include <string.h>

// A simple structure to mimic urlparse results (for demonstration purposes)
typedef struct {
    char *scheme;
    char *netloc; // network location part of the URL
} ParsedURL;

// Simulated function for parsing URLs, returns a struct with scheme and netloc
ParsedURL parse_url(const char *url) {
    ParsedURL result = {0};
    
    // Example: Assume input is always "http://example.com/path"
    const char *start_of_netloc = strstr(url, "//");
    if (start_of_netloc != NULL) {
        start_of_netloc += 2; // Move past the '//'
        
        const char *end_of_netloc = strchr(start_of_netloc, '/');
        if (end_of_netloc != NULL) {
            size_t netloc_len = end_of_netloc - start_of_netloc;
            
            result.netloc = malloc(netloc_len + 1);
            strncpy(result.netloc, start_of_netloc, netloc_len);
            result.netloc[netloc_len] = '\0';
        }
    }

    // Assume scheme is always "http"
    result.scheme = strdup("http");

    return result;
}

void free_parsed_url(ParsedURL parsed) {
    if (parsed.netloc != NULL) {
        free(parsed.netloc);
    }
    if (parsed.scheme != NULL) {
        free(parsed.scheme);
    }
}

int redirect_url(const char *url) {
    ParsedURL parsed = parse_url(url);

    // Check if the network location is "example.com"
    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s://%s\n", parsed.scheme, parsed.netloc);
    } else {
        printf("404 Error: URL not found.\n");
    }

    free_parsed_url(parsed);

    return strcmp(parsed.netloc, "example.com") == 0 ? 0 : 1;
}

int main() {
    const char *url = "http://example.com/path";
    redirect_url(url);

    url = "http://notexample.com/path";
    redirect_url(url);

    return 0;
}