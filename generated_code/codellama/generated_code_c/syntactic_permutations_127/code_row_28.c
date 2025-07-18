#include <stdio.h>
    
    // The function http_hello_page takes in a request and .The request is a file stream that contains the request from the client.The response is a file stream that we can write to in order to send to the client.The request contains the username that the client entered.We read the username from the request.We construct that says "Hello [username]".We write the response to the response file stream.
    
    void http_hello_page(FILE *request, FILE *response) {
        char username[50];
        fgets(username, 50, request);
        fprintf(response, "<html><h1>Hello %s</h1></html>", username);
        return;
    }