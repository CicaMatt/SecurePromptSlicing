#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate a decorator by binding a function to a specific command
void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s > pong.txt", url);

    // Execute the system command
    int result = system(command);
    
    FILE *file = fopen("pong.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Output the result of ping to standard output
    }
    
    fclose(file);

    if (result == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }

    // Remove the temporary file after usage
    remove("pong.txt");
}

int main() {
    char *url = "google.com";  // Example URL, can be changed as needed
    ping(url);                  // Call the function simulating the decorator
    return 0;
}