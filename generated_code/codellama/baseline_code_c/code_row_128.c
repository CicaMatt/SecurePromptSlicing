//request handling function
void http_hello_page(FILE *request, FILE *response){
  //buffer for request data
  char buffer[50];
  
  //read first 50 characters from the request stream into buffer
  fread(buffer, sizeof(char), 50, request);
  
  //find the username in the buffer
  int i;
  for (i=0; i<50; i++){
    if (buffer[i] == '?'){
      break;
    }
  }
  
  //construct the response message "hello [username]"
  char *message = "hello";
  strcat(message, buffer+i+1);
  
  //write the response to the client
  fprintf(response, "%s", message);
}