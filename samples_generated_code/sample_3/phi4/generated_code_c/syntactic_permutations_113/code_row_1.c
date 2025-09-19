#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bind_function_to_url(const char *url) {
    if (strcmp(url, "ping") == 0) {
        char pong[1024];
        // Run ping command and capture the output
        FILE *fp = popen("ping -c 4 google.com", "r");
        if (fp != NULL) {
            while (fgets(pong, sizeof(pong), fp) != NULL) {
                printf("%s", pong);
            }
            pclose(fp);

            // Check return value of the ping command
            int status = WEXITSTATUS(pclose(fp));
            if (status == 0) {
                printf("Ping successful.\n");
            } else {
                printf("Ping failed.\n");
            }
        } else {
            perror("Failed to run command");
        }
    } else {
        printf("URL not recognized.\n");
    }
}

int main() {
    char url[100];
    printf("Enter URL: ");
    fgets(url, sizeof(url), stdin);
    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    bind_function_to_url(url);

    return 0;
}