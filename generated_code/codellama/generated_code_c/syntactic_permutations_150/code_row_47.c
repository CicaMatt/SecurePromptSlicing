#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <mysql/mysql.h>

    // Function to insert message into database
    void insert_user_message_in_db(MYSQL *conn, char *username,char *message) {
        char query[1024];
        sprintf(query,"INSERT INTO messages (username,message) VALUES ('%s','%s')",username, message);
        mysql_query(conn,query);
    }

    // Function to handle form submission
    void post(MYSQL *conn) {
        char username[20];
        char message[256];
        // Get data from request
        get_data(username,message);
        // Insert data into database
        insert_user_message_in_db(conn, username, message);
        // Redirect to main page
        redirect_to_main();
    }