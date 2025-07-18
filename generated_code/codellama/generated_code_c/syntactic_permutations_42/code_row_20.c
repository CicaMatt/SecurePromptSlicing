#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* username;
    char* email;
    int ssn;
} User;

char *info(User user) {
    const char *format = "username: %s\nemail: %s\nsnn: %d\n";
    char *message = malloc(256);
    
    sprintf(message, format, user.username, user.email, user.ssn);
    
    return message;
}