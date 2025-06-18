<html>
    <head>
        <title>Login</title>
    </head>
    <body>
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Login</button>
        </form>
    </body>
<html>



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_db.h"

void login(char* username, char* password)
{
    int exists = 0;
    int i;
    for (i=0; i<10; i++) {
        if (!strcmp(username, db[i][0]) && !strcmp(password, db[i][1])) {
            exists = 1;
            break;
        }
    }
    if (exists) {
        printf("User %s redirected to homepage\n", username);
    } else {
        printf("%s does not exist in the database. Redirecting back to login page\n", username);
    }
}