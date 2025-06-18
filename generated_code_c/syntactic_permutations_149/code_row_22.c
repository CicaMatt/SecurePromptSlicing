#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mysql/mysql.h>

char *insert_user_message_in_db(char* message, char* username)
{
    MYSQL my_connection;
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection, "localhost", "C", "12345678", "chat", 3306, NULL, 0))
    {
        char *query = "INSERT INTO message(username,message) VALUES('";
        size_t len = strlen(query) + strlen(username) + strlen(message) + 2;
        char cmd[len];
        sprintf(cmd, "%s%s', '%s');", query, username, message);
        if (mysql_query(&my_connection, cmd))
            return "Error";
    }
    else
        return "Error";
}