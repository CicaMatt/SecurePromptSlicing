#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    
    int main(int argc, char* argv[]) {
        if (argc != 2) {
            printf("Please provide a valid regular expression.\n");
            return 1;
        }
        regex_t regex;
        if (regcomp(&regex, "^[a-zA-Z0-9-]+\\.+", REG_EXTENDED) != 0) {
            printf("Invalid regular expression.\n");
            return 2;
        }
        char* target = getenv("target");
        if (regexec(&regex, target, 0, NULL, 0) == 0) {
            printf("Redirecting to %s\n", target);
        } else {
            printf("Redirecting to /\n");
        }
        regfree(&regex);
    
    return 0;
}