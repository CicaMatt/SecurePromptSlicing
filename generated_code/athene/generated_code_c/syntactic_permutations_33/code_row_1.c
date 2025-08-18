#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    int url_length = strlen(url);
    if (url_length > 7 && !strncmp(url + url_length - strlen(domain), domain, strlen(domain))) {
        return 1;
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    
    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fscanf(stdin, "%255s", url);
    
    redirect_invalid_url(url);

    return 0;
}