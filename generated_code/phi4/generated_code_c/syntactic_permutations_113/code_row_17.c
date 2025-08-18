#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to execute a command and capture its output
int run_command(const char *url, char *pong) {
    char buffer[128];
    char command[256];

    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    FILE *pipe = popen(command, "r");
    if (!pipe) return -1;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strncat(pong, buffer, sizeof(pong) - strlen(pong) - 1);
    }

    int status = pclose(pipe);
    return WEXITSTATUS(status); // Returns the exit status of the ping command
}

// Function to handle the URL request and check if it's alive
void handle_url_request(const char *url) {
    char pong[1024] = {0};
    int result = run_command(url, pong);

    if (result == 0) {
        printf("URL %s is alive.\n", url);
        printf("Ping output:\n%s\n", pong);
    } else {
        printf("URL %s is not reachable.\n", url);
    }
}

int main() {
    // URL to be pinged
    const char *url = "google.com";

    handle_url_request(url);

    return 0;
}