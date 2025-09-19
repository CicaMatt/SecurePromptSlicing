#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 32

void hash_password(const char *password, char *hashed_password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    snprintf(hashed_password, HASH_SIZE, "%lx", hash);
}

int check_user_exists(MYSQL *conn, const char *username) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[256];
    sprintf(query, "SELECT username FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    int exists = row != NULL;
    mysql_free_result(res);
    return exists;
}

void register_user(MYSQL *conn, const char *username, const char *password, 
                   const char *first_name, const char *last_name, const char *email) {
    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    char query[1024];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) "
                    "VALUES ('%s', '%s', '%s', '%s', '%s')", 
            username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "dbname", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%49s", username);

    if (check_user_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter password: ");
        scanf("%49s", password);
        
        printf("Enter first name: ");
        scanf("%49s", first_name);
        
        printf("Enter last name: ");
        scanf("%49s", last_name);

        printf("Enter email: ");
        scanf("%99s", email);

        register_user(conn, username, password, first_name, last_name, email);
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}