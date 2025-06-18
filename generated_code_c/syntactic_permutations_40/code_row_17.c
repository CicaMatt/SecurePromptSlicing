#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "session_manager.h"

typedef struct {
    char *username;
    char *email;
    int ssn;
} user;

int main() {
    /* Initialize session manager */
    session_manager_init();
    
    /* Set session variable to a user struct */
    user *u = malloc(sizeof(user));
    u->username = "JohnDoe";
    u->email = "johndoe@example.com";
    u->ssn = 1234;
    set_session("user", (void *)u);
    
    /* Get session variable */
    user *r = get_session("user");
    printf("Username: %s\nEmail: %s\nSSN: %d\n", r->username, r->email, r->ssn);
    
    /* Destroy session manager */
    session_manager_destroy();
}