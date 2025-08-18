#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *output;
    char username[] = "your_username"; // Replace your_username with the actual username
    char command[50];

    snprintf(command, sizeof(command), "getent passwd %s", username);
    output = popen(command, "r");
    
    if (output == NULL) {
        perror("popen() failed:");
        exit(EXIT_FAILURE);
    }

    // Example of reading the output
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), output) != NULL) {
        printf("%s", buffer);
    }

    pclose(output);
    return 0;
}