#include <stdlib.h>
#include <stdio.h>

int main() {
    FILE *output;
    char username[100];
    char command[200];

    output = fopen("output.txt", "w");
    if (output == NULL) {
        return 1;
    }

    printf("Enter username: ");
    scanf("%99s", username);

    snprintf(command, sizeof(command), "getent passwd %s", username);
    system(command);

    fclose(output);
    return 0;
}