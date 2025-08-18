#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 33

void hash_password(const char *password, char *hashed) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    sprintf(hashed, "%lx", hash);
}

int check_user_exists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    int exists = atoi(row[0]);
    mysql_free_result(result);

    return exists > 0 ? 1 : 0;
}

int register_user(MYSQL *conn, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    if (check_user_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        if (register_user(conn, username, password, first_name, last_name, email) == 0) {
            printf("Registration succeeded.\n");
        } else {
            printf("Registration failed.\n");
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}