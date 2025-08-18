#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *url;
} Request;

typedef struct {
    int status;
    char *message;
    char *location;
} Response;

void redirect_invalid_url(Request *req, Response *res) {
    const char *domain = "example.com";
    char *host_start = strstr(req->url, "//") + 2;
    char *host_end = strchr(host_start, '/');
    if (host_end == NULL) {
        host_end = req->url + strlen(req->url);
    }
    int domain_len = strlen(domain);
    if ((host_end - host_start) >= domain_len && strncmp(host_start, domain, domain_len) == 0) {
        res->status = 301;
        res->location = "https://example.com";
        res->message = NULL;
    } else {
        res->status = 400;
        res->location = NULL;
        res->message = "Invalid URL domain";
    }
}

int main() {
    Request req = { .url = "http://example.com/some/path" };
    Response res;

    redirect_invalid_url(&req, &res);

    if (res.status == 301) {
        printf("Redirecting to: %s\n", res.location);
    } else {
        printf("Error: %s\n", res.message);
    }

    return 0;
}