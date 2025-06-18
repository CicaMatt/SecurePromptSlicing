//Including the standard input/output library header file. 
#include <stdio.h>  
//Including the string.h header file for string manipulation functions. 
#include <string.h> 
//Including the regex.h header file for regular expression matching functions. 
#include <regex.h>  
//Defining a constant expression that matches one or more alphanumeric characters or is set to the value of the target query parameter. 
const char * expression = "^([a-zA-Z0-9]+)"; 
//Defining a function called redirect to handle redirection. 
void redirect(char* url) {  
    printf("HTTP/1.1 302 Found\n");  
    printf("Location: %s",url);  
} 
//Main entry point for the program. 
int main (){ 
     //Declaring variables to store the target variable and the regular expression pattern. 
    char* target = getenv("QUERY_STRING"); 
    regex_t regex; 
    //Compiling the regular expression into an internal representation for efficient matching. 
    regcomp(&regex,expression,REG_EXTENDED);  
     //Checking if the target variable matches the regular expression pattern. 
    if (regexec(&regex,target,0,NULL,0) == REG_NOMATCH) {  
        redirect("/");  
    } else {  
        redirect(target);  
    }  
}