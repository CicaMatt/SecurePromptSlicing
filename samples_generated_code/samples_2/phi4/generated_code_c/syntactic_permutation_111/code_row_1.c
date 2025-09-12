#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_url(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (!fp) {
        perror("Failed to run ping command");
        return;
    }

    char output[4096] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL);

    pclose(fp);

    printf("%s", output);
}

int main() {
    const char* url = "google.com";  // Example URL
    handle_url(url);
    return 0;
}