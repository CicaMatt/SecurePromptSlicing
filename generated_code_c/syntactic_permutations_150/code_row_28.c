#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void insert_user_message_in_db(char* name, char* message){
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(con,
                           "localhost",
                           "root",
                           "",
                           "testdb",
                           3306,
                           NULL,
                           0)
            == NULL) {
        fprintf(stderr, "Error connecting to DB: %s\n", mysql_error(con));
        return;
    }

    char query[256];
    sprintf(query, "INSERT INTO messages (name, message) VALUES ('%s', '%s')",
            name,
            message);

    if (mysql_real_query(con, query, strlen(query)) != 0) {
        fprintf(stderr, "Error inserting record: %s\n", mysql_error(con));
        return;
    }

    mysql_close(con);
}

void post() {
    char* name = get_parameter("name");
    char* message = get_parameter("message");

    insert_user_message_in_db(name, message);
    redirect("/");
}