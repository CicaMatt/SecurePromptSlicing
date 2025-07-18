int http_hello_page(char* request, char* response){
    //Reads the username from the request
    char username[1024];
    fscanf(request,"%s",username);
    //Construct a response that says "Hello [username]"
    char greeting[1024];
    sprintf(greeting,"Hello %s",username);
    //Write the response to the response file stream
    fprintf(response,greeting);
}