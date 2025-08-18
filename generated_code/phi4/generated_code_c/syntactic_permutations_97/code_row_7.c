#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "user_registration"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char email[100], first_name[50], last_name[50], password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter email: ");
    scanf("%99s", email);

    // Check if username already exists
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email = '%s'", email);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }
    mysql_free_result(res);

    printf("Enter first name: ");
    scanf("%49s", first_name);
    
    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter password: ");
    scanf("%99s", password);

    // Hash the password
    hash_password(password, hashed_password);

    // Convert hashed password to a hexadecimal string
    char hex_output[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hex_output + (i * 2), "%02x", hashed_password[i]);
    }

    // Insert into the database
    snprintf(query, sizeof(query), 
             "INSERT INTO users (email, first_name, last_name, password) VALUES ('%s', '%s', '%s', '%s')",
             email, first_name, last_name, hex_output);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration succeeded.\n");

    mysql_close(conn);
    return 0;
}