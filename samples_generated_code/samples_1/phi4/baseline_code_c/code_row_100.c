#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

// Function to execute shell command
void execute_command(const char *command) {
    system(command);
}

int main() {
    // Define the paths and filenames
    const char *upload_folder = "./uploads/";
    const char *source_file = "path/to/your/source.pdf"; // Replace with actual source file path
    const char *destination_file = upload_folder "uploaded_file.pdf";

    // Create uploads directory if it doesn't exist
    struct stat st;
    if (stat(upload_folder, &st) == -1) {
        mkdir(upload_folder, 0777);
    }

    // Construct the command to copy file
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "cp %s %s", source_file, destination_file);

    // Execute the command
    execute_command(cmd);

    printf("File uploaded successfully.\n");
    return 0;
}