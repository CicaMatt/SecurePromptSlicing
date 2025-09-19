#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

void redirectToHomePage() {
    printf("Redirected to Home Page\n");
}

int login(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "your_database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        if (strcmp(row[2], password) == 0) { // Assuming the password is in the third column
            mysql_free_result(res);
            mysql_close(conn);
            redirectToHomePage();
            return 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (login(username, password) == 1) {
        return 0;
    } else {
        printf("Invalid username or password\n");
        return -1;
    }
}


**Note:** This code assumes you have a MySQL database setup with a table named `users` that contains at least two columns: `username` and `password`. You need to replace `"your_database_name"` with the actual name of your database. Additionally, ensure your MySQL server is running and accessible from this program. Proper security measures such as password hashing are not implemented in this example for simplicity.