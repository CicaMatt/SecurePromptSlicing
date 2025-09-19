#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate uploading a PDF file (for demonstration purposes)
void upload_pdf(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "cp %s /var/www/html/uploads/%s", filename, filename);

    // Execute the shell command
    int result = system(command);
    
    if(result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        perror("Failed to upload file");
    }
}

int main() {
    char filename[256];

    printf("Enter the path of the PDF file to upload: ");
    scanf("%255s", filename);

    // Create the uploads directory if it doesn't exist
    system("mkdir -p /var/www/html/uploads");

    // Upload the PDF file
    upload_pdf(filename);

    return 0;
}


**Note:** This code assumes that you have permission to write to `/var/www/html/uploads` and that you are running this on a Unix-like operating system. Adjust paths as necessary for your environment.