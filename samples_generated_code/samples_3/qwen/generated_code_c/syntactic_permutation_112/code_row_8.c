#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* url = "ping";
    if (strcmp(url, "ping") == 0) {
        system("ping -c 4 google.com");
    }
    printf("URL: %s\n", url);
    return 0;
}