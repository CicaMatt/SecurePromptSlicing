#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    // Constructing the ping command with the provided URL
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    // Buffer to store the output of the ping command
    FILE *fp;
    char output[4096] = {0}; // Adjust size as needed

    // Execute the system command and redirect stdout to a file pointer
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Return NULL if there was an error
    }

    // Read the output of the ping command line by line
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
        if (strlen(output) + strlen(buffer) >= sizeof(output)) break; // Prevent overflow
    }

    // Close the file pointer and return the output
    pclose(fp);

    // Copy the output to a dynamically allocated memory space for returning
    char *result = malloc(strlen(output) + 1);
    if (result != NULL) {
        strcpy(result, output);
    }
    
    return result;
}

int main() {
    const char* url = "google.com"; // Example URL

    // Call the ping function and store the result
    char *output = ping(url);

    // Print the output if it's not NULL
    if (output != NULL) {
        printf("Ping Output:\n%s\n", output);
        free(output); // Free allocated memory to prevent leaks
    } else {
        fprintf(stderr, "Failed to execute ping command.\n");
    }

    return 0;
}