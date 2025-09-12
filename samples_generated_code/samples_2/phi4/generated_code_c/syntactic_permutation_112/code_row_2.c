#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *url) {
    if (strcmp(url, "ping") == 0) {
        printf("Pinging...\n");
        system("ping -c 4 google.com"); // Example ping command
    } else {
        printf("URL not recognized.\n");
    }
}

int main() {
    const char *url = "ping"; // This would be the requested URL

    handle_request(url);

    return 0;
}