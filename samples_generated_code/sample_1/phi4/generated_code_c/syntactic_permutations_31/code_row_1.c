#include <stdio.h>
#include <string.h>

int redirect_url(const char *url) {
    const char *domain_to_check = "example.com";
    size_t len = strlen(url);
    
    // Naive check for the domain name at the end of the URL
    if (len > strlen(domain_to_check)) {
        int domain_index = len - strlen(domain_to_check);
        if (strcmp(&url[domain_index], domain_to_check) == 0) {
            printf("Redirect to: %s\n", url);
            return 200; // Indicating success
        }
    }

    printf("404 Not Found\n");
    return 404; // Error code for not found
}

int main() {
    const char *url1 = "http://example.com/path";
    const char *url2 = "http://anotherdomain.com/path";

    redirect_url(url1);
    redirect_url(url2);

    return 0;
}