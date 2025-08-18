#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple structure to represent a parsed URL
typedef struct {
    char* scheme;
    char* netloc;  // Network location, equivalent to domain in this context
    char* path;
} ParsedURL;

// Function prototypes
ParsedURL parse_url(const char* url);
void free_parsed_url(ParsedURL parsed);

void redirect_url(const char* url) {
    ParsedURL parsed = parse_url(url);

    if (parsed.netloc != NULL) {
        printf("Redirecting to domain: %s\n", parsed.netloc);
    } else {
        printf("Invalid URL.\n");
    }

    free_parsed_url(parsed);
}

ParsedURL parse_url(const char* url) {
    ParsedURL result = {0};
    const char* delimiter;
    size_t len;

    // Allocate memory for components
    result.scheme = malloc(256 * sizeof(char));
    result.netloc = malloc(256 * sizeof(char));
    result.path = malloc(1024 * sizeof(char));

    if (result.scheme == NULL || result.netloc == NULL || result.path == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Find the scheme
    delimiter = strchr(url, ':');
    if (delimiter != NULL && strncmp(url, "http", 4) == 0 && *(delimiter + 1) == '/') {
        len = delimiter - url;
        strncpy(result.scheme, url, len);
        result.scheme[len] = '\0';
        
        // Find the netloc
        delimiter += 3; // Skip "://"
        const char* start = delimiter;
        delimiter = strchr(delimiter, '/');
        if (delimiter != NULL) {
            len = delimiter - start;
            strncpy(result.netloc, start, len);
            result.netloc[len] = '\0';
            
            // Find the path
            strncpy(result.path, delimiter, 1023);
            result.path[1023] = '\0';
        }
    }

    if (result.scheme[0] == '\0' || result.netloc[0] == '\0') {
        free(result.scheme);
        free(result.netloc);
        free(result.path);
        return (ParsedURL){0};
    }

    return result;
}

void free_parsed_url(ParsedURL parsed) {
    if (parsed.scheme != NULL) {
        free(parsed.scheme);
    }
    if (parsed.netloc != NULL) {
        free(parsed.netloc);
    }
    if (parsed.path != NULL) {
        free(parsed.path);
    }
}

int main() {
    const char* url = "http://example.com/path/to/resource";
    redirect_url(url);

    return 0;
}