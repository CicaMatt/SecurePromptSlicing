#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to send the file as a response
void send_file(char* name)
{
    // Open the file and read it in binary mode
    FILE *fptr;
    fptr = fopen(name, "rb");

    // Read the contents of the file into buffer
    char buff[256];
    while(!feof(fptr)) {
        fread(&buff, 1, sizeof(buff), fptr);
        printf("%s", buff);
    }
}

// Decorator function to associate the URL /img with this function
void img()
{
    // Get the name parameter from the URL and open the file
    char* name;
    sscanf(getenv("QUERY_STRING"), "name=%s", &name);
    send_file(name);
}