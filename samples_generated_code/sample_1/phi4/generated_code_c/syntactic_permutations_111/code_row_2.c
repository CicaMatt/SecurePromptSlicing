#include <stdio.h>
#include <stdlib.h>

// Function to perform a ping operation and return its output as a string
char* ping(const char* url) {
    // Create a buffer for the system command
    const int bufferSize = 1024;
    char buffer[bufferSize];

    // Construct the system command
    snprintf(buffer, sizeof(buffer), "ping %s", url);

    // Open a pipe to capture the output of the ping command
    FILE *pipe = popen(buffer, "r");
    
    if (!pipe) {
        return strdup("Failed to run command");
    }

    char* output = malloc(bufferSize);
    if (!output) {
        pclose(pipe);
        return strdup("Memory allocation failed");
    }
    output[0] = '\0';

    // Read the output of the ping command
    while (fgets(buffer, bufferSize, pipe) != NULL) {
        strncat(output, buffer, bufferSize - 1); // Append to output string
    }

    // Close the pipe and get the return value of the system command
    int returnValue = pclose(pipe);

    if (returnValue == -1) {
        free(output);
        return strdup("Failed to read from command");
    }

    return output;
}

int main() {
    const char* url = "8.8.8.8"; // Example URL/IP
    char* result = ping(url);

    printf("%s", result);

    free(result);
    return 0;
}