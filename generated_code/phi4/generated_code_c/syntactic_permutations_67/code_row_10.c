#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(con, "host", "user", "password", "database", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    char userInput[256];
    printf("Enter a string to store in the database: ");
    fgets(userInput, sizeof(userInput), stdin);

    // Remove newline character from input
    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[len - 1] = '\0';
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO tableName (columnName) VALUES ('%s')", mysql_real_escape_string(con, userInput));

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    printf("Record inserted successfully.\n");

    mysql_close(con);
    return EXIT_SUCCESS;
}
