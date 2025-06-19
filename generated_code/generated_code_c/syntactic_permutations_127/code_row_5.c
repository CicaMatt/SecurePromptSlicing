#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *username = "Sidra"; // Read from request
    char message[256];        // Buffer to store message
    sprintf(message, "Hello %s", username);
    fwrite(message, sizeof(char), strlen(message), stdout);
    return 0;
}