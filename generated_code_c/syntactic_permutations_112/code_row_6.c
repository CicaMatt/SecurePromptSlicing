#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Decorator for URL binding
void bind_url(const char* url) {
    // Function to run when the URL is requested
    void ping() {
        // Run the ping command using system()
        int rc = system("ping " + url);
        if (rc != 0)
            exit(1); // Exit on error
    }
}