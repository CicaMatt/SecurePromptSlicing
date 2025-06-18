#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include<mysql/mysql.h>

    // MySQL Connection Information
    const char* server = "localhost";
    const char* user = "root";
    const char* password = "";
    const char* database = "mydb";

    // Insert Message into Database Function
    void insert_user_message_in_db(MYSQL *conn,const char* username,const char* message){
        char query[255];
        sprintf(query,"INSERT INTO messages (username,message) VALUES('%s','%s')",username,message);
        mysql_query(conn,query);
    }

    // Post Function
    void post(MYSQL *conn){
        const char* username = mysql_real_escape_string(conn,getenv("QUERY_STRING"));
        const char* message = mysql_real_escape_string(conn,getenv("REQUEST_METHOD"));
        insert_user_message_in_db(conn,username,message);
    }

    int main() {
        // Create a MySQL Connection Object
        MYSQL *conn;
        conn = mysql_init(NULL);

        // Connect to the Database
        if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            printf("Connection Successful!\n");
            post(conn);
        } else {
            printf("Connection Failed!\n");
        }

        // Close the Connection
        mysql_close(conn);
    }