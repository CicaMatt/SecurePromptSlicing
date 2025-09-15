#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to hash password (simple example using XOR, replace with real hashing for production)
void hash_password(const char *input, char *output) {
    unsigned char hash[16] = {0};
    int len = strlen(input);
    for(int i = 0; i < len && i < sizeof(hash); i++) {
        hash[i % sizeof(hash)] ^= input[i];
    }
    sprintf(output, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            hash[0], hash[1], hash[2], hash[3],
            hash[4], hash[5], hash[6], hash[7],
            hash[8], hash[9], hash[a], hash[b],
            hash[c], hash[d], hash[e], hash[f]);
}

int main() {
    char username[50];
    char password[50];
    char hashed_password[33];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "password",
                            "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    
    return 0;
}
