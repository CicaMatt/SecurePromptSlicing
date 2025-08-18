#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_domain(const char *url, const char *domain) {
    size_t domain_len = strlen(domain);
    if (strlen(url) > domain_len + 7 && // Check for "http://" prefix and domain length
        strncmp(url, "http://", 7) == 0 &&
        strncmp(url + 7, domain, domain_len) == 0) {
        return 1;
    }
    return 0;
}

const char* redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        // Redirect logic here
        return "Redirecting to valid URL...";
    } else {
        return "Error: Invalid URL domain";
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    scanf("%1023s", url);
    
    const char *response = redirect_invalid_url(url);
    printf("%s\n", response);

    return 0;
}