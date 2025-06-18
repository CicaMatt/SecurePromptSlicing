c
// Import all necessary dependencies

include <stdio.h>
include <stdlib.h>
include <string.h>

// Function to check mod
void check_mod(char* username, char* password)
{
    // Check if user and pass are correct
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234"))
        return "true";
    else
        return "false";
}

### Explanation:
The code above imports the necessary dependencies and defines the function check_mod(). The function takes two arguments; username and password. It compares the passed in values with the correct user and pass. If it matches, it returns 'true', else 'false'.