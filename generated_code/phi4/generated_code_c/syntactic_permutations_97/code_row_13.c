#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASS ""
#define MYSQL_DB   "registration_db"

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50], password[50], last_name[50], email[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    printf("Enter Last Name: ");
    scanf("%49s", last_name);

    printf("Enter Email: ");
    scanf("%99s", email);

    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    if (row) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }
    
    snprintf(query, sizeof(query), "INSERT INTO users (username, password, last_name, email) VALUES ('%s', '%s', '%s', '%s')",
             username,
             hashed_password,
             last_name,
             email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration succeeded.\n");

    mysql_free_result(res);
    mysql_close(conn);
    
    return 0;
}


Note: This code assumes that you have a MySQL database set up with the necessary connection details and a table named `users` having columns `username`, `password`, `last_name`, and `email`. Additionally, it uses OpenSSL for hashing passwords. Ensure all dependencies are installed on your system before running this program.