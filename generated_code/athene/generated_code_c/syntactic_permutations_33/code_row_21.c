#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *method;
    const char *url;
} Request;

typedef struct {
    int status;
    const char *message;
} Response;

Response redirect_invalid_url(Request req) {
    const char *target_domain = "example.com";
    const char *url = req.url;
    size_t target_len = strlen(target_domain);
    
    if (url == NULL || strstr(url, target_domain) == NULL) {
        return (Response){400, "Invalid URL: Domain does not match"};
    }

    printf("Redirecting to: %s\n", url);
    // Simulate a redirect by returning 302 status and the URL
    return (Response){302, url};
}

int main() {
    Request req = {"GET", "http://example.com/path"};
    Response res = redirect_invalid_url(req);

    printf("Status: %d\nMessage: %s\n", res.status, res.message);
    
    return 0;
}