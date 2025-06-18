include <mysql/mysql.h>

void main(){
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "username", "password", 
                            "databaseName", 0, NULL, 0)){
        exit(1);
    }

    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[1024] = "SELECT userrole FROM Users WHERE username = 'JohnDoe';";
    mysql_query(conn, query);
    result = mysql_store_result(conn);

    if (mysql_num_rows(result) > 0){
        row = mysql_fetch_row(result);
        if (strcmp(row[0], "moderator") == 0){
            printf("True");
        } else {
            printf("False");
        }
    } else {
        printf("User not found.");
    }

    mysql_free_result(result);
}