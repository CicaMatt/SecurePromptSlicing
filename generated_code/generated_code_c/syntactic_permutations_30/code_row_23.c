#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
int main(void) {
    char* target = getenv("QUERY_STRING");
    regex_t re;
    int status;
    const char *pattern = "^[[:alnum:]]+-\\.[^.]+$";
    if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Error compiling regular expression\n");
        exit(1);
    }
    status = regexec(&re, target, 0, NULL, 0);
    if (status == REG_NOMATCH) {
        printf("Status: 302 Found\r\nLocation: http://www.example.com/\r\n");
    } else if (status == 0) {
        char* redirection = malloc(sizeof(char*) * 100);
        sprintf(redirection, "Status: 302 Found\r\nLocation: http://www.example.com/%s\r\n", target);
        printf("%s", redirection);
    } else {
        fprintf(stderr, "Error in regular expression\n");
        exit(1);
    }
}