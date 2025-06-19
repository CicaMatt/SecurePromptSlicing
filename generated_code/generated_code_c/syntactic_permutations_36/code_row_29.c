#include <stdio.h>
#include <stdlib.h>
#include "database/db_query.h"

void login(char *username, char *password) {
    // Query database for user with the given username
    User *user = query_user_by_username(username);
    if (!user) {
        return;
    }
    
    // Check if password matches hashed value in database
    if (check_password(password, user->password)) {
        redirect_to_home_page();
    } else {
        return;
    }
}