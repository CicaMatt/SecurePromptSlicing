#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    sprintf(hashed, "%lx", hash);
}

int register_user(MYSQL *conn, const char *username, const char *hashed_password, 
                  const char *first_name, const char *last_name, const char *email) {
    
    if (mysql_query(conn, "SELECT COUNT(*) FROM users WHERE username = ?")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    long count = atoll(row[0]);
    mysql_free_result(result);

    if (count > 0) {
        printf("Username already exists.\n");
        return 0;
    }
    
    char query[256];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
            username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    printf("Registration succeeded.\n");
    return 1;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed.\n");
        return EXIT_FAILURE;
    }
    
    conn = mysql_real_connect(conn, "localhost", "root", "", "test_db", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
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
    
    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    if (!register_user(conn, username, hashed_password, first_name, last_name, email)) {
        fprintf(stderr, "Registration failed.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}