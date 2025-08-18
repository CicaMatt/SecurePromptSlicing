#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define NAME_LEN 50
#define EMAIL_LEN 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int check_username_exists(MYSQL *conn, const char *username) {
    int exists = 0;
    char query[1024];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result)) && strcmp(row[0], "0") != 0) {
        exists = 1;
    }
    mysql_free_result(result);
    return exists;
}

void insert_user(MYSQL *conn, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH], const char *first_name, const char *last_name, const char *email) {
    char password_str[PASSWORD_LEN];
    snprintf(password_str, sizeof(password_str), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
             hashed_password[0],  hashed_password[1],  hashed_password[2],  hashed_password[3],
             hashed_password[4],  hashed_password[5],  hashed_password[6],  hashed_password[7],
             hashed_password[8],  hashed_password[9],  hashed_password[10], hashed_password[11],
             hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15]);

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, password_str, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char first_name[NAME_LEN];
    char last_name[NAME_LEN];
    char email[EMAIL_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned char hashed_password[SHA256_DIGEST_LENGTH];
        hash_password(password, hashed_password);
        insert_user(conn, username, hashed_password, first_name, last_name, email);
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return 0;
}