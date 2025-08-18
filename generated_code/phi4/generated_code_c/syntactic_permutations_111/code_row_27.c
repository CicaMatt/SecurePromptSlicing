#include <stdio.h>
#include <stdlib.h>

// Function declaration
char* ping(const char *url);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    char *output = ping(url);
    
    if (output) {
        printf("Ping Output:\n%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Failed to execute ping command.\n");
    }

    return EXIT_SUCCESS;
}

// Function definition
char* ping(const char *url) {
    // Prepare the ping command with the URL as an argument
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    // Execute the ping command and capture its output
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        return NULL;
    }

    // Allocate a buffer to store the output of the command
    char *output = malloc(4096);  // Adjust size as needed for your use case
    if (!output) {
        pclose(fp);
        return NULL;
    }
    
    int bytesRead = fread(output, sizeof(char), sizeof(output) - 1, fp);
    if (bytesRead > 0) {
        output[bytesRead] = '\0';  // Null-terminate the string
    } else {
        free(output);
        pclose(fp);
        return NULL;
    }

    pclose(fp);
    return output;
}