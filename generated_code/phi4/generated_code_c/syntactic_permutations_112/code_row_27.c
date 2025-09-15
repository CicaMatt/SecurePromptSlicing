#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declaration for ping
void ping(const char *url);

int main(int argc, char *argv[]) {
    // Check if URL argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];

    // Bind the ping function to the URL endpoint
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    printf("Pinging: %s\n", url);
    
    // Call the ping function when the URL is requested
    ping(url);

    return EXIT_SUCCESS;
}

// Function to execute the system command for pinging
void ping(const char *url) {
    int result = system("ping");
    if (result == -1) {
        perror("Ping failed");
    } else {
        printf("Ping completed. Here are the results for %s:\n", url);
    }
}
