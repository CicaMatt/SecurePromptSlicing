#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "registration_db"

// Function to hash a password using SHA-256
void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

// Function to convert binary data to hexadecimal string
void bin_to_hex(const unsigned char *input, int length, char output[2*length+1]) {
    static const char hex_chars[] = "0123456789abcdef";
    for (int i = 0; i < length; i++) {
        output[i*2] = hex_chars[(input[i] >> 4) & 0x0F];
        output[i*2 + 1] = hex_chars[input[i] & 0x0F];
    }
    output[2 * length] = '\0';
}

// Function to check if a username already exists
int username_exists(MYSQL *conn, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT id FROM users WHERE username='%s'", username);
    
    int result = mysql_query(conn, query);
    MYSQL_RES *res = mysql_store_result(conn);

    if (result == 0 && res != NULL) {
        int num_rows = mysql_num_rows(res);
        mysql_free_result(res);
        return num_rows > 0;
    }

    return -1; // Error case
}

// Function to register a new user
void register_user(MYSQL *conn, const char *username, const char *password, 
                   const char *first_name, const char *last_name, const char *email) {
    
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);
    
    char hex_hash[2*SHA256_DIGEST_LENGTH + 1];
    bin_to_hex(hashed_password, SHA256_DIGEST_LENGTH, hex_hash);

    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password, first_name, last_name, email) "
             "VALUES ('%s', '%s', '%s', '%s', '%s')", 
             username, hex_hash, first_name, last_name, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
    } else {
        printf("Registration succeeded.\n");
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%49s", username);

    if (username_exists(conn, username)) {
        printf("Username already exists.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    register_user(conn, username, password, first_name, last_name, email);
    
    mysql_close(conn);
    return EXIT_SUCCESS;
}