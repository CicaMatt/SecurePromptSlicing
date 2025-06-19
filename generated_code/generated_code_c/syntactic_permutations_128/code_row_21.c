#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <http.h>

char *http_hello_page(struct http_request *request, struct http_response *response)
{
    // Extract the username from the request.
    char *username = request->query_params[0];

    // Construct a response that says "Hello, [username]!" and write it to the response.
    char *message = malloc(1024);
    sprintf(message, "Hello, %s!", username);
    http_response_write(response, message);

    // Send the response back to the client.
    return response;
}