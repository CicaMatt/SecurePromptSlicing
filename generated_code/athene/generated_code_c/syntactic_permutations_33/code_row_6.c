#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    char *host_start, *host_end;
    host_start = strstr(url, "//");
    if (host_start == NULL) return 0;
    host_start += 2;
    host_end = strchr(host_start, '/');
    if (host_end == NULL) host_end = host_start + strlen(host_start);
    char host[100];
    strncpy(host, host_start, host_end - host_start);
    host[host_end - host_start] = '\0';
    return strstr(host, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}