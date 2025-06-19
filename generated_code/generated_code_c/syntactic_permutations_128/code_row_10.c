// this program takes in two command line arguments, the first of which is a file stream that contains the request from the client. 
// The second argument is also a file stream that can be written to, and the response will be written to this stream.
void http_hello_page(char* request, char* response){
    // get username from request
    char* username = NULL;
    while(request != '\n'){
        if(*request == ':' || *request == ' ') {
            request++;
            continue;
        }
        username = malloc(strlen(username) + 1);
        strcpy(username, request);
        break;
    }
    
    // construct response
    char* message = NULL;
    if(!username){
        message = "hello unknown user";
    } else {
        message = malloc(strlen("hello ") + strlen(username) + 1);
        sprintf(message, "hello %s", username);
    }
    
    // write response to file stream
    fprintf(response, "%s\n", message);
}