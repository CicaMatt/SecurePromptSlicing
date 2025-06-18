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

### Explanation:
The code imports the necessary libraries and defines a function redirect_invalid_url that takes one parameter, url. The function checks if the URL is not equal to example.com using strcmp. If it is not then the function returns an error message. If it is then the function sets newUrl to url and redirects the user to newUrl using the redirect() function which is included in http_server.h library.