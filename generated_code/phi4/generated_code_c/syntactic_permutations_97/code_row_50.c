#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 60
#define FIRSTNAME_LEN 50
#define LASTNAME_LEN 50
#define EMAIL_LEN 100

void hash_password(const char *password, char *hashed_password) {
    // Simple hashing function (not secure for production use)
    unsigned int hash = 0;
    while (*password) {
        hash = ((hash << 5) + hash) + (unsigned char)(*password++);
    }
    sprintf(hashed_password, "%u", hash);
}

int check_username_exists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0 ? 1 : 0;
}

int register_user(MYSQL *conn, const char *username, const char *hashed_password, 
                  const char *first_name, const char *last_name, const char *email) {
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) "
                                  "VALUES ('%s', '%s', '%s', '%s', '%s')", 
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

    conn = mysql_real_connect(conn, "localhost", "root", "password", "test_db", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "Connection Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char first_name[FIRSTNAME_LEN];
    char last_name[LASTNAME_LEN];
    char email[EMAIL_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_SUCCESS;
    }

    printf("Enter password: ");
    scanf("%59s", password);

    char hashed_password[PASSWORD_LEN];
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, hashed_password, first_name, last_name, email) == 0) {
        printf("Registration succeeded.\n");
    } else {
        printf("Registration failed.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}