#include <stdio.h>
#include <stdlib.h>

void handlePingRequest(const char *url) {
    printf("Pinging %s...\n", url);
    
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s > ping_output.txt", url);

    int result = system(command);
    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }

    FILE *file = fopen("ping_output.txt", "r");
    if (file != NULL) {
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);

        remove("ping_output.txt");
    } else {
        printf("Failed to read ping output.\n");
    }
}

int main() {
    const char *url = "example.com";
    handlePingRequest(url);
    return 0;
}