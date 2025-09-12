#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed_password) {
    // Simple hashing function using XOR for demonstration purposes.
    unsigned long hash = 0;
    while (*password) {
        hash ^= (unsigned long)(*password++);
        if (*password) hash *= 103; // Prime number multiplication
    }
    snprintf(hashed_password, HASH_SIZE, "%lx", hash);
}

int check_username_exists(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0;
}

int register_user(MYSQL *conn, const char *username, const char *password, 
                  const char *first_name, const char *last_name, const char *email) {
    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    if (check_username_exists(conn, username)) {
        return 0; // Username exists
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash, first_name, last_name, email) "
             "VALUES ('%s', '%s', '%s', '%s', '%s')", 
             username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return 0;
    }

    return 1; // Registration succeeded
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed.\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "", "database_name", 0, NULL, 0);
    if (!conn) {
        fprintf(stderr, "Connection Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[100], password[100], first_name[50], last_name[50], email[100];
    
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, password, first_name, last_name, email)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Username already exists.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}