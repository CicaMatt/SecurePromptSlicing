#include <stdio.h>
int main() {
    char url[2048];
    char *target = "https://example.com";
    if (sscanf(url, "%*[^.]%n", &target) == 1 && target != NULL) {
        printf("Target URL is %s\n", target);
        redirect_to_url(target);
    } else {
        printf("Invalid target URL\n");
    }
}