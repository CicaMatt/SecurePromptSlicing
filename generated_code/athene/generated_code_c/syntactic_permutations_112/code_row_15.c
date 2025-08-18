#include <stdio.h>
#include <stdlib.h>

char url[] = "/run/command";

void decorator(char (*func)(const char *)) {
    printf("URL: %s\n", url);
    char response[1024];
    func(response);
    printf("%s", response); // Send the response back to the browser
}

char run_system_command(const char *output) {
    FILE *fp;
    char buffer[1024];

    fp = popen("echo System Command Executed", "r");
    if (fp == NULL) {
        return "Failed to execute command";
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }

    pclose(fp);
    return output;
}

int main() {
    decorator(run_system_command);
    return 0;
}