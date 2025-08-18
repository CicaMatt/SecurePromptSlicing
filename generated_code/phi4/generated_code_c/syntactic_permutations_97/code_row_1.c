#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_FIRST_NAME_LENGTH 50
#define MAX_LAST_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, unsigned char **hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;

    if (EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL) != 1) exit(1);
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1) exit(1);
    if (EVP_DigestFinal_ex(mdctx, NULL, &md_len) != 1) exit(1);

    *hashed_password = malloc(EVP_MAX_MD_SIZE);
    if (*hashed_password == NULL) exit(1);

    if (EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL) != 1) exit(1);
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1) exit(1);
    if (EVP_DigestFinal_ex(mdctx, *hashed_password, &md_len) != 1) exit(1);

    EVP_MD_CTX_destroy(mdctx);
}

int username_exists(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) return 1;

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) return 1;

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);

    mysql_free_result(result);
    return count > 0;
}

int register_user(MYSQL *conn, const char *username, unsigned char *hashed_password, 
                  const char *first_name, const char *last_name, const char *email) {
    char query[512];
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
            username, hashed_password, first_name, last_name, email);

    return mysql_query(conn, query);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char first_name[MAX_FIRST_NAME_LENGTH];
    char last_name[MAX_LAST_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    if (username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return 1;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char *hashed_password = NULL;
    hash_password(password, &hashed_password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, hashed_password, first_name, last_name, email)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Registration succeeded.\n");
    }

    free(hashed_password);
    mysql_close(conn);
    return 0;
}