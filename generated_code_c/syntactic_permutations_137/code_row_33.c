/*
 *  File name: check_mod.c
 *  Author: Your Name
 *  Date created: Date
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "auth_mod.c"

#define MAX_LENGTH 1024

void check_mod(char *username, char *password, char *session)
{
    if (auth_mod(username, password, session))
    {
        printf("The user is authenticated!\n");
    }
    else
    {
        printf("The user is not authenticated!\n");
    }
}