#include <stdio.h>
void http_hello_page(FILE *request, FILE *response)
{
    char username[1024];
    fscanf(request, "%s", username);
    fprintf(response, "hello %s\n", username);
}

### Explanation:
We include the stdio.h library to make use of the FILE data type and the fscanf function.
The function takes in two parameters, request and response, both of which are files streams.
We create an array username of size 1024 to store the client's input, which can be up to 1023 characters long.
We use the fscanf function to read from the request file stream into the username variable. The %s specifier reads a string of characters until it reaches a whitespace character.
The fprintf function writes to the response file stream and sends a response back to the client. It includes the "hello" keyword and the contents of the username variable, which is the client's input.