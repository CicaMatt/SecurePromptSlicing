#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char* command) {
    FILE *fp;
    char path[1035];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }

    pclose(fp);
}

int main() {
    char username[256];
    printf("Enter username: ");
    scanf("%255s", username);

    char command[300];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);

    executeCommand(command);

    return 0;
}