#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "bcrypt.h"

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "userdb"

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    char username[50], password[100];
    
    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    // Hash the password using bcrypt
    char *hashed_password = bcrypt_hashpw(password, "$2a$12$somesalt");

    if (hashed_password == NULL) {
        fprintf(stderr, "Password hashing failed\n");
        mysql_close(con);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             username, hashed_password);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    printf("Registration successful!\n");

    mysql_close(con);
    free(hashed_password); // Free the memory allocated by bcrypt
    return 0;
}
