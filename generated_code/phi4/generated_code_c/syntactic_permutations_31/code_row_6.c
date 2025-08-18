#include <stdio.h>
#include <string.h>

// Dummy URL parsing function for demonstration purposes
typedef struct {
    char* scheme;
    char* netloc; // Network location (domain)
} ParsedURL;

ParsedURL parse_url(const char* url) {
    ParsedURL parsed;
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        const char* netloc_start = strstr(url + (url[4] == 's' ? 8 : 7), "/");
        if (netloc_start != NULL) {
            netloc_start = strchr(netloc_start - 1, '/');
            parsed.netloc = strndup(netloc_start + 1, strlen(url) - (netloc_start - url));
        } else {
            parsed.netloc = strdup(url + (url[4] == 's' ? 8 : 7));
        }
    } else {
        parsed.netloc = NULL;
    }
    return parsed;
}

void free_parsed_url(ParsedURL* parsed) {
    if (parsed->netloc != NULL) {
        free(parsed->netloc);
    }
}

void redirect_url(const char* url) {
    ParsedURL parsed = parse_url(url);

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Not Found: The domain name is not example.com\n");
    }

    free_parsed_url(&parsed);
}

int main() {
    redirect_url("http://example.com/resource");
    redirect_url("https://anotherdomain.com/page");
    return 0;
}