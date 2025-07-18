// Import libraries
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "http_server.h"

int redirect_invalid_url(char* url) {
    if (strcmp(url, "example.com") != 0) { // If the URL is not example.com
        return "Invalid URL"; // Return error message
    }

    char* newUrl = url; // Set newUrl to url
    redirect(newUrl); // Redirect user to newUrl
}
