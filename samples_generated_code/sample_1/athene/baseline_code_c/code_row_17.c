#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"
#define DB_HOST "localhost"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char insert_query[256];
    snprintf(insert_query, sizeof(insert_query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x)",
             username,
             hashed_password[0],  hashed_password[1],  hashed_password[2],  hashed_password[3],
             hashed_password[4],  hashed_password[5],  hashed_password[6],  hashed_password[7],
             hashed_password[8],  hashed_password[9],  hashed_password[10], hashed_password[11],
             hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15],
             hashed_password[16], hashed_password[17], hashed_password[18], hashed_password[19],
             hashed_password[20], hashed_password[21], hashed_password[22], hashed_password[23],
             hashed_password[24], hashed_password[25], hashed_password[26], hashed_password[27],
             hashed_password[28], hashed_password[29], hashed_password[30], hashed_password[31]);

    if (mysql_query(conn, insert_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User added successfully.\n");

    mysql_close(conn);
    return 0;
}