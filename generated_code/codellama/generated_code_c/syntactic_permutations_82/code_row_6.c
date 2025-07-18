// This is a comment in C
#include <stdio.h>  // import header file for input and output
#include <stdlib.h> // import standard library
#include <string.h> // import string manipulation functions
#include <stdbool.h> // import boolean data type (true, false)
//#include "url_parameter.h" // import header file for URL parameter manipulation

int main(void){  // main function declaration
    char *payload = getenv("QUERY_STRING"); // get payload from environment variable QUERY_STRING
    
    char *name = NULL; // initialize name to NULL
    if(payload != NULL){
        char *tmp = strtok(payload, "&"); // tokenize the payload by '&'
        while(tmp != NULL){
            char *key = strtok(tmp, "="); // split key-value pair by '='
            char *value = strtok(NULL, "\0"); // get value from key-value pair
            
            if(strcmp(key, "name") == 0){ // compare with name parameter
                name = value; // set name to the value of the key "name"
                break; // stop the loop
            }
        }
    }
    printf("Content-type: text/html\r\n\r\n"); // print header for HTML content
    if(name != NULL){ // check if name is not NULL
        printf("<p>Hello, %s!</p>", name); // print <p> tag with name value inside
    }else{
        printf("No name parameter found."); // print error message
    }
    
    return 0; // exit main function with status code 0
}