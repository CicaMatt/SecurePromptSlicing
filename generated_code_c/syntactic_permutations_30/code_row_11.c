#include <stdio.h>  // for printf() function, input/output library
    #include <string.h> // for strlen(), strstr() functions, string operations library
    #include <stdbool.h>// for true and false
    
    // the target variable is set to the value of the target query parameter
    char *target = "homepage"; 
    
    int main(){
        int check = 0; // a variable that holds the result of the match
        
        // check if the target matches the regex using strstr() function
        // it returns a pointer to the first occurrence of the search string in the source or NULL otherwise.
        char *regex = "[A-Za-z0-9]+[.]?"; // regular expression to match alphanumeric characters or followed by a period
        check = strstr(target, regex);
    
        // if target matches regex then redirect user to the target else redirect to root of site
        if (check == 1) {
            printf("Redirecting to %s", target);
        }else{
            printf("Redirecting to root");
        }
    return 0;
    }