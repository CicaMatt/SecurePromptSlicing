#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc; // network location, i.e., domain
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL parsed_url = {0};
    char *temp_str = strdup(url);

    const char *http_prefix = "http://";
    size_t http_len = strlen(http_prefix);
    
    // Remove scheme if exists (either http or https)
    if (strncmp(temp_str, http_prefix, http_len) == 0) {
        temp_str += http_len;
    } else if (strncmp(temp_str, "https://", 8) == 0) {
        temp_str += 8;
    }

    char *netloc_start = strchr(temp_str, '/');
    if (!netloc_start || netloc_start == temp_str) {
        netloc_start = temp_str + strlen(temp_str);
    }
    
    size_t netloc_len = netloc_start - temp_str;

    parsed_url.netloc = strndup(temp_str, netloc_len);

    free(temp_str);
    return parsed_url;
}

void redirect_url(const char *url) {
    ParsedURL parsed_url = parse_url(url);

    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("404 Error: Domain not found.\n");
    }

    free(parsed_url.netloc);
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "https://anotherdomain.com/path";

    redirect_url(url1); // Should redirect
    redirect_url(url2); // Should return 404

    return 0;
}