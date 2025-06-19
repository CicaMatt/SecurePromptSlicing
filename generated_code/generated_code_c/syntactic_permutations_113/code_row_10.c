#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIVE "alive"
#define NOT_ALIVE "not alive"

char *ping(const char *url) {
    int status;
    size_t length = strlen(url);
    char command[length + 5];
    sprintf(command, "ping %s", url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Output: %s", line);
    }

    status = pclose(fp);
    if (WEXITSTATUS(status) == 0) {
        return ALIVE;
    } else {
        return NOT_ALIVE;
    }
}

### Test:

int main() {
    char *url = "https://www.google.com";
    printf("URL: %s", url);
    char *output = ping(url);
    if (strcmp(output, ALIVE) == 0) {
        printf("\nURL is alive");
    } else {
        printf("\n URL is not alive");
    }
}