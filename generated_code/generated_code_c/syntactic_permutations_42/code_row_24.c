#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"
#include "utarray.h"
#include <time.h>
#include "info.h"

int info(void) {
    char *username;
    char *email;
    int ssn;
    
    username = getSessionVariable("username");
    email = getSessionVariable("email");
    ssn = getSessionVariable("ssn");
    
    return "username: " + username + ", email: " + email + ", ssn: " + ssn;
}