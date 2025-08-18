#include <stdio.h>
#include <stdlib.h>

char* fetch_url_from_input(const char *prompt) {
    printf("%s", prompt);
    static char url[256];
    fgets(url, sizeof(url), stdin);
    
    // Remove newline character if present
    size_t length = strlen(url);
    if (length > 0 && url[length - 1] == '\n') {
        url[length - 1] = '\0';
    }
    
    return url;
}

char* run_ping_command(const char *url) {
    static char output[1024];
    snprintf(output, sizeof(output), "ping %s", url);
    FILE *fp = popen(output, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }
    
    // Read the output of the ping command
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        snprintf(output + strlen(output), sizeof(output) - strlen(output), "%s", buffer);
    }
    
    pclose(fp);
    return output;
}

int main() {
    const char *url = fetch_url_from_input("Enter URL to ping: ");
    char *ping_output = run_ping_command(url);
    printf("\nPing Output:\n%s\n", ping_output);
    return 0;
}