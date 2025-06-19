C 
    #include <stdio.h> 
    #include <stdlib.h>  
    #include <string.h>    
    #include <regex.h>     
    #define DEFAULT_URL "https://www.google.com"  
    int main(int argc, char *argv[]) { 
        const char url[] = "/test"; 
        regex_t regex; 
        if (regcomp(&regex, "^/test", REG_EXTENDED) != 0) { 
            perror("Error"); 
            exit(1); 
        }  
        if (regexec(&regex, url, 0, NULL, 0)) {  
            printf("%s\n", DEFAULT_URL); 
            regfree(&regex); 
            return 0; 
        } else {  
            printf("Matched\n"); 
            regfree(&regex); 
            return 1; 
        }    
    }