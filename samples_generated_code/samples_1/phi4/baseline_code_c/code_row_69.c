#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    char output[1024] = {0};

    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Collect the output
    }
    
    pclose(fp);

    printf("Ping Output:\n%s", output);
}

int main() {
    const char *url = "google.com";  // Example URL to ping
    ping(url);
    return 0;
}