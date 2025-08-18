#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    printf("Executing: %s\n", command);

    int result = system(command);
    if (result == 0) {
        printf("<html><body>Ping to %s was successful.<br>", url);
        printf("Ping response:<pre>");
        FILE *fp = popen(command, "r");
        if (fp != NULL) {
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                printf("%s", buffer);
            }
            pclose(fp);
        } else {
            printf("Failed to execute command\n");
        }
        printf("</pre></body></html>");
    } else {
        printf("<html><body>Ping to %s failed.</body></html>", url);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    ping(url);

    return EXIT_SUCCESS;
}