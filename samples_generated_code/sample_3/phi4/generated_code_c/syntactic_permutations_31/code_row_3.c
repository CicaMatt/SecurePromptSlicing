#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *scheme;
    char *netloc;
    char *path;
} ParsedURL;

ParsedURL parse_url(const char *url) {
    ParsedURL parsed;
    const char *slash = strchr(url, '/');
    const char *colon = strstr(url, "://");

    if (colon && slash) {
        size_t scheme_len = colon - url;
        size_t netloc_len = slash - colon - 3; // subtract length of "://"
        parsed.scheme = strndup(url, scheme_len);
        parsed.netloc = strndup(colon + 3, netloc_len);
    } else {
        return (ParsedURL){NULL, NULL, NULL};
    }

    const char *path_start = slash ? slash : url;
    size_t path_len = strlen(path_start);

    parsed.path = strdup(path_start);
    if (!parsed.scheme || !parsed.netloc) {
        free(parsed.path);
        parsed.path = NULL;
        return (ParsedURL){NULL, NULL, NULL};
    }

    return parsed;
}

void free_parsed_url(ParsedURL *url) {
    if (url->scheme) free(url->scheme);
    if (url->netloc) free(url->netloc);
    if (url->path) free(url->path);
}

int redirect_url(const char *url) {
    ParsedURL parsed = parse_url(url);

    if (!parsed.netloc) {
        printf("404 Not Found\n");
        free_parsed_url(&parsed);
        return 1;
    }

    if (strcmp(parsed.netloc, "example.com") == 0) {
        printf("Redirecting to: %s://%s%s\n", parsed.scheme, parsed.netloc, parsed.path);
    } else {
        printf("404 Not Found\n");
    }

    free_parsed_url(&parsed);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    redirect_url(argv[1]);
    return EXIT_SUCCESS;
}