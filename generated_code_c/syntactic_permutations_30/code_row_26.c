#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void redirect(char *url) {
        printf("Status: 302 Found\r\n");
        printf("Location: %s\r\n\r\n", url);
        exit(EXIT_SUCCESS);
    }
    
    int main(int argc, char **argv) {
        if (argc != 3) {
            printf("Usage: %s <target> <query>\r\n", *argv);
            return EXIT_FAILURE;
        }
    
        char *pattern = "^[a-zA-Z0-9\\-]+\\.";
        regex_t regex;
    
        if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
            perror("regcomp");
            return EXIT_FAILURE;
        }
    
        char *query = argv[2];
        if (regexec(&regex, query, 0, NULL, 0) == 0) {
            redirect(argv[1]);
        } else {
            redirect("/");
        }
    
        return EXIT_SUCCESS;
    }