#include <stdio.h>
#include <string.h>

// Mockup of a basic HTTP request structure for demonstration purposes.
typedef struct {
    char method[8];
    char url[128];
} HttpRequest;

// Mockup of a basic file object structure for demonstration purposes.
typedef struct {
    const char *filename;
    FILE *file;
} FileObject;

// Function to simulate sending a response back to the browser.
void send_response(FileObject file_obj) {
    if (file_obj.file != NULL) {
        // Send the file content as response
        printf("Sending file: %s\n", file_obj.filename);
        fclose(file_obj.file);
    } else {
        printf("File not found.\n");
    }
}

// Decorator function that associates the URL /img with img_function
FileObject img_decorator(HttpRequest request) {
    if (strcmp(request.method, "GET") == 0 && strstr(request.url, "/img/") != NULL) {
        char filename[128];
        
        // Extract filename from the URL after "/img/"
        const char *filename_start = strstr(request.url, "/img/") + strlen("/img/");
        strncpy(filename, filename_start, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
        
        return img_function(filename);
    }
    
    // Return an empty file object if not matched
    FileObject empty_file_obj = { .filename = "", .file = NULL };
    return empty_file_obj;
}

// Function that returns a file object based on the filename parameter
FileObject img_function(const char *filename) {
    FILE *file = fopen(filename, "rb");
    
    FileObject file_obj = { .filename = filename, .file = file };
    return file_obj;
}

int main() {
    // Example HttpRequest simulation
    HttpRequest request = {"GET", "/img/example.png"};
    
    // Use the decorator to process the request and get a response
    FileObject response_file = img_decorator(request);
    send_response(response_file);

    return 0;
}