#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MYSQL_USER "root"
#define MYSQL_PASS ""
#define MYSQL_DB   "test_db"

void check_mysql_connection(MYSQL *conn);
void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]);
int register_user(const char *username, const char *firstname, const char *lastname, const char *email, unsigned char password_hash[SHA256_DIGEST_LENGTH]);

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    check_mysql_connection(conn);

    char username[50], firstname[50], lastname[50], email[100];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter first name: ");
    scanf("%49s", firstname);
    printf("Enter last name: ");
    scanf("%49s", lastname);
    printf("Enter email: ");
    scanf("%99s", email);

    char password[50];
    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, password_hash);

    int result = register_user(username, firstname, lastname, email, password_hash);

    if (result == 1) {
        printf("Username already exists.\n");
    } else if (result == 0) {
        printf("Registration succeeded.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}

void check_mysql_connection(MYSQL *conn) {
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASS, MYSQL_DB, 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
}

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int register_user(const char *username, const char *firstname, const char *lastname, const char *email, unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    check_mysql_connection(conn);

    char query[512];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    int count = atoi(row[0]);
    mysql_free_result(result);

    if (count > 0) {
        mysql_close(conn);
        return 1; // Username exists
    }

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i * 2], "%02x", password_hash[i]);
    }
    
    snprintf(query, sizeof(query), "INSERT INTO users (username, firstname, lastname, email, password) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, firstname, lastname, email, hashed_password);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    mysql_close(conn);
    return 0; // Registration succeeded
}