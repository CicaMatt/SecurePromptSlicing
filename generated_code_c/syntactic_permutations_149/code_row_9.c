#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    int insert_user_message_in_db(const char *name, const char *message)
    {
        MYSQL *conn;
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn,
                                "localhost",
                                "root",
                                "",
                                NULL,
                                0,
                                NULL,
                                0))
        {
            return 1;
        }

        char query[50];
        sprintf(query, "INSERT INTO messages VALUES ('%s', '%s')", name, message);
        int err = mysql_query(conn, query);
        if (err)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void display_messages()
    {
        MYSQL *conn;
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn,
                                "localhost",
                                "root",
                                "",
                                NULL,
                                0,
                                NULL,
                                0))
        {
            return 1;
        }

        char query[50];
        sprintf(query, "SELECT * FROM messages");
        int err = mysql_query(conn, query);
        if (err)
        {
            return 1;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        while (MYSQL_ROW row = mysql_fetch_row(result))
        {
            printf("%s\n", row[0]);
            printf("%s\n", row[1]);
        }
    }

    int main()
    {
        insert_user_message_in_db("Rick Sanchez", "Wubba Lubba Dub Dub!");
        display_messages();
        return 0;
    }