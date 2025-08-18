#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed) {
    // Simple hash function (for demonstration purposes)
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    snprintf(hashed, HASH_SIZE, "%lx", hash);
}

int user_exists(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "Store result error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int exists = atoi(row[0]);
    mysql_free_result(result);

    return exists > 0;
}

int main() {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[256], password[256], first_name[256], last_name[256], email[256];
    char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);
    printf("Enter first name: ");
    scanf("%255s", first_name);
    printf("Enter last name: ");
    scanf("%255s", last_name);
    printf("Enter email: ");
    scanf("%255s", email);

    if (user_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    hash_password(password, hashed_password);

    char query[512];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
            username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Registration succeeded.\n");

    mysql_close(conn);
    return EXIT_SUCCESS;
}