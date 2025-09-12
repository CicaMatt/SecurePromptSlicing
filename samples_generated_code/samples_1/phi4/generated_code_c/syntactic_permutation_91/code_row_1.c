#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "test_db"

void hash_password(const char *password, unsigned char hashed[20]) {
    SHA1((unsigned char *)password, strlen(password), hashed);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = SERVER;
    const char *user = USER;
    const char *pass = PASSWORD;
    const char *database = DATABASE;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, pass, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter your name: ");
    char name[100];
    scanf("%99s", name);

    printf("Enter your password: ");
    char password[100];
    scanf("%99s", password);

    unsigned char hashed_password[20];
    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (name, password) VALUES ('%s', '%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x')", 
             name,
             hashed_password[0], hashed_password[1], hashed_password[2], hashed_password[3],
             hashed_password[4], hashed_password[5], hashed_password[6], hashed_password[7],
             hashed_password[8], hashed_password[9], hashed_password[10], hashed_password[11],
             hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15],
             hashed_password[16], hashed_password[17], hashed_password[18], hashed_password[19]);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration successful!\n");

    mysql_close(conn);

    return 0;
}


**Note:** Ensure that the MySQL server is running and the database `test_db` with a table named `users` having columns `name` (VARCHAR) and `password` (CHAR[40]) exists. Additionally, you need to have OpenSSL library installed for SHA1 hashing.