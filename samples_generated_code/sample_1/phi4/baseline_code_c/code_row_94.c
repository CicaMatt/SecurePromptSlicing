#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUF_SIZE 256

unsigned long hash_password(const char *password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char username[BUF_SIZE];
    char password[BUF_SIZE];
    unsigned long hashed_password;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter username: ");
    fgets(username, BUF_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, BUF_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    hashed_password = hash_password(password);

    char query[BUF_SIZE * 2];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', %lu)", username, hashed_password);

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
- Create a database named `test_db` and a table `users` with columns `username` (VARCHAR) and `password` (UNSIGNED LONG).
- Update the MySQL connection parameters as needed (`localhost`, `root`, password, etc.).
- Compile using: `gcc -o registration registration.c $(mysql_config --cflags --libs)`