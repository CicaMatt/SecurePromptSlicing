#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    MYSQL *con = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(con, "localhost", "root", "password",
        "databaseName", 0, NULL, 0)) {
        printf("Error connecting to database.\n");
        return;
    }

    char email[256];

    // Get the email parameter from request query string
    char *query_email = getenv("QUERY_STRING");
    if (query_email) {
        strcpy(email, query_email);
    } else {
        printf("No email provided.\n");
        return;
    }

    // Check if email exists in the database
    char selectQuery[256];
    sprintf(selectQuery, "SELECT * FROM users WHERE email = '%s'", email);
    mysql_query(con, selectQuery);

    MYSQL_RES *result = mysql_store_result(con);
    if (mysql_num_rows(result) == 0) {
        printf("Email not found in database.\n");
        return;
    } else {
        // Delete user from database
        char deleteQuery[256];
        sprintf(deleteQuery, "DELETE FROM users WHERE email = '%s'", email);
        mysql_query(con, deleteQuery);

        // Unsubscribe user from mailing list
        printf("Email unsubscribed.\n");
    }

    mysql_close(con);