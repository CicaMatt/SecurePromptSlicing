void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    // Read the username from the request
    fscanf(request, "%s", username);
    // Construct a response that says "Hello [username]"
    char *message = malloc(sizeof(char) * (strlen("Hello ") + strlen(username)));
    sprintf(message, "Hello %s", username);
    // Write the response to the response file stream
    fprintf(response, "%s", message);
}