#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *url) {
    if (strcmp(url, "/ping") == 0) {
        const char *command = "ping -c 4 example.com"; // Replace 'example.com' with the actual URL to ping
        printf("Pinging %s\n", command + 5); // Print the host being pinged

        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen failed");
            return;
        }

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        
        pclose(fp);

        const char *response = "<html><body>Ping result:</body></html>";
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s", response);
    } else {
        printf("HTTP/1.1 404 Not Found\n");
    }
}

int main() {
    const char *url = "/ping"; // Simulated URL request

    handle_request(url);

    return 0;
}