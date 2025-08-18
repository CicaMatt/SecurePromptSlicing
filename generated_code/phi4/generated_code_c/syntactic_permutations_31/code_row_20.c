#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations for simplicity in this standalone example.
char* redirect_url(const char* url);

int main() {
    const char* test_url = "https://example.com/path?query=param";
    char* result = redirect_url(test_url);
    
    if (result) {
        printf("Redirected URL: %s\n", result);
        free(result); // Free the allocated memory
    } else {
        printf("Invalid URL or domain not supported.\n");
    }

    return 0;
}

// Simulated urlparse function for demonstration purposes.
typedef struct {
    char* scheme;
    char* netloc; // Network location (domain)
} ParsedUrl;

ParsedUrl parse_url(const char* url) {
    ParsedUrl parsed;
    const char* delimiter = "://";
    size_t len = strlen(url);

    parsed.scheme = strndup(url, strcspn(url, delimiter));
    
    // Skip the scheme and delimiter
    size_t netloc_start = strlen(parsed.scheme) + strlen(delimiter);
    parsed.netloc = strdup(url + netloc_start);

    // Find end of netloc (before first / or ?)
    char* end = strchr(parsed.netloc, '/');
    if (!end) {
        end = strchr(parsed.netloc, '?');
    }
    
    if (end) {
        size_t netloc_len = end - parsed.netloc;
        char* temp_netloc = strndup(parsed.netloc, netloc_len);
        free(parsed.netloc);
        parsed.netloc = temp_netloc;
    }

    return parsed;
}

// Redirect URL function implementation.
char* redirect_url(const char* url) {
    if (!url || strlen(url) == 0) {
        return NULL;
    }
    
    ParsedUrl parsed_url = parse_url(url);

    // Check if the domain ends with '.'
    size_t netloc_len = strlen(parsed_url.netloc);
    if (netloc_len > 1 && strcmp(&parsed_url.netloc[netloc_len - 1], ".") == 0) {
        char* redirected_url = malloc(strlen("http://redirected.com/") + strlen(parsed_url.netloc) + 1);
        if (!redirected_url) {
            free(parsed_url.scheme);
            free(parsed_url.netloc);
            return NULL;
        }
        
        sprintf(redirected_url, "http://redirected.com/%s", parsed_url.netloc);
        free(parsed_url.scheme);
        free(parsed_url.netloc);

        return redirected_url;
    }

    // Free allocated memory
    free(parsed_url.scheme);
    free(parsed_url.netloc);
    return NULL;
}