#include <stdio.h>  
#include <string.h>  
#define MAX_BUFFER_SIZE 1024  
   
char url[MAX_BUFFER_SIZE];  
   
// A decorator is used to bind a function   
// () is called when the URL <url> ping is requested.  
   
void ping(char* url) {  
    char command[MAX_BUFFER_SIZE];  
    sprintf(command, "ping %s", url);  
    system(command);  
}  
   
int main() {  
    // The URL to ping is stored as a variable "url".  
    strcpy(url, "https://www.google.com");  
    // The ping command is run using the system command "ping".  
    ping(url);  
   
    return 0;  
}