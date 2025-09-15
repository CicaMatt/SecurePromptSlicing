#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "registration_db"

void hashPassword(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)password, strlen(password), hashed);
}

int checkIfUsernameExists(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

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

void registerUser(MYSQL *conn, const char *username, unsigned char hashedPassword[SHA256_DIGEST_LENGTH], 
                  const char *firstName, const char *lastName, const char *email) {
    char query[512];
    sprintf(query, "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES ('%s', '%.*s', '%s', '%s', '%s')", 
            username, SHA256_DIGEST_LENGTH, hashedPassword, firstName, lastName, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Registration succeeded.\n");
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed.\n");
        return 1;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char username[256], password[256], firstName[256], lastName[256], email[256];
    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);
    printf("Enter first name: ");
    scanf("%255s", firstName);
    printf("Enter last name: ");
    scanf("%255s", lastName);
    printf("Enter email: ");
    scanf("%255s", email);

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    if (checkIfUsernameExists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        registerUser(conn, username, hashedPassword, firstName, lastName, email);
    }

    mysql_close(conn);
    return 0;
}
