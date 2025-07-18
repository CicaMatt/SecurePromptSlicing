void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    fgets(username, 256, request);
    const char* message = "Hello ";
    int responseLength = strlen(message) + strlen(username);
    char responseMessage[responseLength];
    sprintf(responseMessage, "%s%s", message, username);
    fputs(responseMessage, response);
}