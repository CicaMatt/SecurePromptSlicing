#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: URL does not belong to example.com\n");
    }
}

int main() {
    char url1[] = "http://www.example.com/page";
    char url2[] = "https://www.otherdomain.com/home";

    redirect_invalid_url(url1); // Should redirect
    redirect_invalid_url(url2); // Should return error

    return 0;
}