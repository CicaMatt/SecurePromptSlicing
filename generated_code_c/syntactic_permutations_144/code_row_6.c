++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if exists in the database. If it doesn't it returns 0. If it does it calls a script that unsubscribes . If the script returns 0 it returns 1. If not it returns 0.
int check_unsubscribe(char* email) {
    // open database connection
    int status = 0;
    if (database_exists(email)) {
        system("./unsubcribe_script");
        status = 1;
    } else {
        status = 0;
    }
    return status;
}