#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PASSWORD_LENGTH 64

void sha256_hash(const unsigned char* input, size_t length, unsigned char output[32]) {
    // Dummy hash function for illustration. Replace with real SHA-256 implementation.
    memset(output, 'a', 32); // Simulating a hash
}

int check_username_exists(MYSQL *conn, const char *username) {
    char query[128];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1; // Error
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    return count > 0;
}

int register_user(MYSQL *conn, const char *username, const char *password, 
                  const char *first_name, const char *last_name, const char *email) {
    unsigned char hashed_password[PASSWORD_LENGTH];
    sha256_hash((const unsigned char*) password, strlen(password), hashed_password);

    char query[512];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%.*s', '%s', '%s', '%s')", 
            username, 32, hashed_password, first_name, last_name, email);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1; // Error
    }

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    
    printf("Enter username: ");
    scanf("%49s", username);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return 1;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, password, first_name, last_name, email)) {
        printf("Failed to register user.\n");
    } else {
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return 0;
}