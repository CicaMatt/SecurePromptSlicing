#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    static char output[1024];
    
    // Create the system command string
    char command[2048];
    snprintf(command, sizeof(command), "ping %s", url);
    
    // Redirect the output of the ping command to a temporary file
    FILE *temp = tmpfile();
    if (temp == NULL) {
        perror("tmpfile");
        return "";
    }
    
    int status = system(command " > temp_output.txt 2>&1"); // Capture both stdout and stderr
    
    // Read the output from the file
    FILE *outputFile = fopen("temp_output.txt", "r");
    if (outputFile == NULL) {
        perror("fopen");
        return "";
    }
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), outputFile)) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }

    fclose(outputFile);
    remove("temp_output.txt");

    return output;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char* url = argv[1];
    printf("Ping Output:\n%s\n", ping(url));
    
    return EXIT_SUCCESS;
}