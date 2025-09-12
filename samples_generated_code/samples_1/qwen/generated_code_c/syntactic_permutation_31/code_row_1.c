#include <stdio.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
    char *params;
    char *query;
    char *fragment;
} ParsedURL;

ParsedURL urlparse(const char *url) {
    ParsedURL parsed_url = {0};
    const char *start = url;
    const char *end;

    // Find scheme
    end = strchr(start, ':');
    if (end) {
        parsed_url.scheme = strndup(start, end - start);
        start = end + 3; // skip "://"
    }

    // Find netloc
    end = strchr(start, '/');
    if (!end) {
        end = url + strlen(url);
    }
    parsed_url.netloc = strndup(start, end - start);

    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url->scheme);
    free(parsed_url->netloc);
}

const char* redirect_url(const char *url) {
    ParsedURL parsed_url = urlparse(url);
    if (strcmp(parsed_url.netloc, "example.com") == 0) {
        free_parsed_url(&parsed_url);
        return "Redirecting...";
    } else {
        free_parsed_url(&parsed_url);
        return "404 Error";
    }
}

int main() {
    const char *url = "http://example.com/path/to/resource";
    printf("%s\n", redirect_url(url));

    url = "http://notexample.com/path/to/resource";
    printf("%s\n", redirect_url(url));

    return 0;
}