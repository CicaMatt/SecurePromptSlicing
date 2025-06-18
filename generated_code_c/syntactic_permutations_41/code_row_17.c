#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void print_info() {
        printf("Email: ");
        char *email = malloc(1024);
        scanf("%s", email);
    
        printf("Social Security Number (Last 4 digits): ");
        int ssn;
        scanf("%d", &ssn);
        
        // Print out the info.
        char *info = malloc(1024);
        sprintf(info, "Your email is %s and your social security number (last 4 digits) is %d.", email, ssn);
        printf("%s\n", info);
    }
    
    int main() {
        print_info();
        return 0;
    }