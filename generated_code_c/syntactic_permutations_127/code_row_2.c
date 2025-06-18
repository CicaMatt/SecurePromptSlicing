// function to handle http requests and return responses
void http_hello_page(FILE *request, FILE *response) {
    // read username from request
    char username[100];
    fscanf(request, "%s", username);

    // construct response message
    char *message = "Hello";
    strcat(message, username);

    // write response to file stream
    fprintf(response, "%s", message);
}