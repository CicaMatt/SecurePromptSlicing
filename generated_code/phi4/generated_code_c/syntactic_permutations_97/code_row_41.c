#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define HASH_SIZE 20

void hash_password(const char *password, unsigned char hash[HASH_SIZE]) {
    SHA1((unsigned char *)password, strlen(password), hash);
}

int insert_user(MYSQL *conn, const char *username, const char *hashed_password, 
                const char *first_name, const char *last_name, const char *email) {
    
    char query[512];
    snprintf(query, sizeof(query),
             "INSERT INTO users (username, password_hash, first_name, last_name, email) "
             "VALUES ('%s', '%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x', "
             "'%s', '%s', '%s')", 
             username,
             hashed_password[0], hashed_password[1], hashed_password[2], hashed_password[3],
             hashed_password[4], hashed_password[5], hashed_password[6], hashed_password[7],
             hashed_password[8], hashed_password[9], hashed_password[10], hashed_password[11],
             hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15],
             hashed_password[16], hashed_password[17], hashed_password[18], hashed_password[19],
             first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }
    
    return 1;
}

int user_exists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

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

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char username[256], password[256], first_name[256], last_name[256], email[256];
    
    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);
    printf("Enter first name: ");
    scanf("%255s", first_name);
    printf("Enter last name: ");
    scanf("%255s", last_name);
    printf("Enter email: ");
    scanf("%255s", email);

    if (user_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned char hashed_password[HASH_SIZE];
        hash_password(password, hashed_password);
        
        if (insert_user(conn, username, hashed_password, first_name, last_name, email)) {
            printf("Registration succeeded.\n");
        } else {
            printf("Registration failed.\n");
        }
    }

    mysql_close(conn);

    return 0;
}