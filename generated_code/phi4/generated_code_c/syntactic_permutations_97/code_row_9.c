#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER   "root"
#define PASSWORD "your_password"
#define DATABASE "test_db"

unsigned long hash_password(const char *password) {
    unsigned long hashed = 5381;
    int c;

    while ((c = *password++)) {
        hashed = (((hashed << 5) + hashed) + c) % 2147483647; /* hash * 33 + c */
    }
    return hashed;
}

int check_username_exists(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0;
}

void register_user(MYSQL *conn, const char *username, unsigned long hashed_password) {
    char query[512];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%lu')", username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter First Name: ");
    scanf("%49s", first_name);

    printf("Enter Last Name: ");
    scanf("%49s", last_name);

    printf("Enter Email: ");
    scanf("%99s", email);

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned long hashed_password = hash_password(password);
        register_user(conn, username, hashed_password);
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return 0;
}