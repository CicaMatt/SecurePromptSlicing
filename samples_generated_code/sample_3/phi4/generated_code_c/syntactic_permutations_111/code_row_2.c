#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    // Create a buffer to hold the command string
    size_t buffer_size = 256;
    char command[buffer_size];

    // Construct the system command
    snprintf(command, buffer_size, "ping %s", url);

    // Run the command and get the output into a pipe
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run ping command.\n");
        return NULL;
    }

    // Allocate memory for the output
    size_t output_size = 1024;
    char *output = malloc(output_size);
    if (!output) {
        perror("Failed to allocate memory");
        pclose(pipe);
        return NULL;
    }
    
    // Read the command output into buffer
    size_t bytes_read = fread(output, 1, output_size - 1, pipe);

    // Null-terminate the string
    if (bytes_read < output_size) {
        output[bytes_read] = '\0';
    } else {
        output[output_size - 1] = '\0'; // Ensure null termination even if full buffer is read
    }

    // Close the pipe and free memory in case of error or completion
    int status = pclose(pipe);
    if (status == -1) {
        free(output);
        fprintf(stderr, "Failed to close pipe.\n");
        return NULL;
    } else if (WIFEXITED(status)) {
        // Check exit status for errors
        if (WEXITSTATUS(status) != 0) {
            free(output);
            fprintf(stderr, "Ping command failed with status %d\n", WEXITSTATUS(status));
            return NULL;
        }
    }

    // Return the output of ping command
    return output;
}

int main() {
    const char *url = "8.8.8.8";  // Example URL to ping
    char *output = ping(url);
    
    if (output) {
        printf("Ping Output:\n%s\n", output);
        free(output);  // Free allocated memory for the output
    }

    return 0;
}