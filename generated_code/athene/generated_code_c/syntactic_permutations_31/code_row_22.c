#include <stdio.h>
#include <string.h>

char* urlparse(const char* url, char* host) {
    const char* start = strstr(url, "//");
    if (start == NULL) return NULL;
    start += 2;
    const char* end = strchr(start, '/');
    if (end == NULL) end = start + strlen(start);
    int len = end - start;
    strncpy(host, start, len);
    host[len] = '\0';
    return host;
}

void redirect_url(const char* url) {
    char domain[256];
    if (urlparse(url, domain) && strcmp(domain, "example.com") == 0) {
        printf("Domain is example.com\n");
    } else {
        printf("Domain is not example.com\n");
    }
}

int main() {
    const char* url = "http://example.com/path";
    redirect_url(url);
    return 0;
}