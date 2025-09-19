#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to hash the password (simple hashing for demonstration)
void simpleHash(char *input, char *output) {
    unsigned int i;
    unsigned long hash = 5381;
    for (i = 0; input[i] != '\0'; i++)
        hash = ((hash << 5) + hash) + input[i];
    sprintf(output, "%lx", hash);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Use your MySQL root password
    const char *database = "test_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50], passwordInput[50], hashedPassword[20];
    
    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", passwordInput);

    simpleHash(passwordInput, hashedPassword);

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
            mysql_real_escape_string(conn, username), 
            mysql_real_escape_string(conn, hashedPassword));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);

    return 0;
}


Before running this code, ensure you have the MySQL C client library installed and a database named `test_db` with a table `users` having columns `username` and `password`. Adjust connection parameters as necessary.