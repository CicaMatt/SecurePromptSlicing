#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(EXIT_FAILURE);
}

char* hash_password(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);

    static char hex_output[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hex_output + (i * 2), "%02x", hash[i]);
    }
    return hex_output;
}

void register_user(const char* username, const char* password, const char* first_name, 
                   const char* last_name, const char* email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "your_database", 3306, NULL, 0)) {
        handle_error(conn);
    }

    char query[BUFFER_SIZE];
    sprintf(query, "SELECT username FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    if (row) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return;
    }
    mysql_free_result(res);

    char hashed_password[2 * SHA256_DIGEST_LENGTH + 1];
    strcpy(hashed_password, hash_password(password));

    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", 
            username, hashed_password, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    printf("Registration succeeded.\n");
    mysql_close(conn);
}

int main() {
    char username[BUFFER_SIZE], password[BUFFER_SIZE], first_name[BUFFER_SIZE], 
         last_name[BUFFER_SIZE], email[BUFFER_SIZE];

    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Enter first name: ");
    fgets(first_name, BUFFER_SIZE, stdin);
    first_name[strcspn(first_name, "\n")] = '\0';

    printf("Enter last name: ");
    fgets(last_name, BUFFER_SIZE, stdin);
    last_name[strcspn(last_name, "\n")] = '\0';

    printf("Enter email: ");
    fgets(email, BUFFER_SIZE, stdin);
    email[strcspn(email, "\n")] = '\0';

    register_user(username, password, first_name, last_name, email);

    return 0;
}