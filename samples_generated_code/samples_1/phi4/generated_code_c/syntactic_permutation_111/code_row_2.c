#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_from_request(const char *url) {
    // Simulated retrieval of URL from request
    return strdup(url);
}

char* run_ping_command(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (!fp) {
        return NULL;
    }

    char output[4096] = {0};
    fread(output, sizeof(char), sizeof(output) - 1, fp);
    pclose(fp);

    return strdup(output);
}

char* ping(const char *url) {
    const char *resolved_url = get_url_from_request(url);
    if (!resolved_url) {
        return NULL;
    }

    char *output = run_ping_command(resolved_url);
    free((void*) resolved_url);

    return output;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* url = argv[1];
    char* result = ping(url);

    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to ping the URL.\n");
    }

    return EXIT_SUCCESS;
}