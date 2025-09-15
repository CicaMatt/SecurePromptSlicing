#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to hash the password (simple example using XOR)
unsigned char* simple_hash(const unsigned char *input, size_t len) {
    unsigned char *hash = malloc(len);
    if (!hash) return NULL;
    for (size_t i = 0; i < len; ++i) {
        hash[i] = input[i] ^ 0xAA; // Simple XOR with a constant
    }
    return hash;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[100];
    unsigned char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", (char *)password);

    // Hash the password
    unsigned char *hashed_password = simple_hash(password, strlen((char *)password));
    if (!hashed_password) {
        fprintf(stderr, "Failed to hash password\n");
        return 1;
    }

    // Connect to database
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Prepare SQL statement
    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%.*s')",
            username, (int)strlen((char *)hashed_password), hashed_password);

    // Execute SQL statement
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(hashed_password);
        mysql_close(conn);
        return 1;
    }

    printf("User registered successfully.\n");

    // Cleanup
    free(hashed_password);
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
