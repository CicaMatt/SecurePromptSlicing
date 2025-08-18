#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void hash_password(char *password, char *hashed_password) {
    unsigned long length = 0;
    for (int i = 0; password[i] != '\0'; ++i)
        hashed_password[length++] = 'X'; // Simple hashing example
    hashed_password[length] = '\0';
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";  // Set your MySQL password here
    const char *database = "test_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[100];
    char password_input[100];
    char hashed_password[101];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password_input);

    hash_password(password_input, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, username),
             mysql_real_escape_string(conn, hashed_password));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Registration successful!\n");

    mysql_close(conn);

    return 0;
}


**Note**: To run this code:
- Ensure you have MySQL installed and running.
- Create a database named `test_db` and a table named `users` with columns `username` (VARCHAR) and `password` (VARCHAR).
- Update the `user`, `password`, and `database` variables to match your MySQL credentials.