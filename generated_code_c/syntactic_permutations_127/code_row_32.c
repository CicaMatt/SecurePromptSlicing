#include <stdio.h>
void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    fscanf(request, "%s", username);
    fprintf(response, "Hello %s!", username);
}

### Explanation:

The request and response are file streams. The function http_hello_page reads the username from the request using the fscanf function. Then it writes a string to the response using the fprintf function. The format of the string is "Hello [username]", where [username] is replaced with the actual username read from the request.