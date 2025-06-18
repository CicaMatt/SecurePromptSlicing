#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database_query.h"

int main(void)
{
    User *user = get_current_user();
    if (user == NULL) {
        redirect("/login");
    } else if (!is_admin(user)) {
        redirect("/users/" + user->id);
    }
}

int is_admin(User *user)
{
    char *sql = "SELECT admin FROM users WHERE id=?";
    int is_admin;
    database_query(sql, &is_admin, user->id);
    return is_admin;
}

void redirect(char *url)
{
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", url);
    printf("\r\n");
    exit(EXIT_SUCCESS);
}