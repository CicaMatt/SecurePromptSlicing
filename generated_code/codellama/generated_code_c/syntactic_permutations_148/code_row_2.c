#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#define SERVER "localhost"
#define USERNAME "root"
#define DATABASE_NAME "messages_board"
#define PASSWORD ""
void insert_user_message_in_db(char* username, char* message);
int main()
{
    return 0;
}
void post()
{
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, DATABASE_NAME, 3306, NULL, 0)) {
        printf("Error : %s\n", mysql_error(conn));
        return;
    }
    char username[1024];
    char message[1024];
    sprintf(username,"%s",mysql_real_escape_string(conn, getenv("HTTP_USERNAME")));
    sprintf(message,"%s",mysql_real_escape_string(conn, getenv("HTTP_MESSAGE")));
    insert_user_message_in_db(username, message);
    char* sql = "INSERT INTO messages (username, message) VALUES ('%s', '%s')";
    if (mysql_query(conn,sql)) {
        printf("Error : %s\n", mysql_error(conn));
    }
    mysql_close(conn);
}
void display_messages()
{
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USERNAME, PASSWORD, DATABASE_NAME, 3306, NULL, 0)) {
        printf("Error : %s\n", mysql_error(conn));
        return;
    }
    char* sql = "SELECT * FROM messages";
    MYSQL_RES* res = mysql_query(conn, sql);
    int num_fields = mysql_num_fields(res);
    while (MYSQL_ROW row = mysql_fetch_row(res)) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i]);
        }
        printf("\n");
    }
    mysql_free_result(res);
    mysql_close(conn);
}