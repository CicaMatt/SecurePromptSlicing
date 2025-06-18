include<stdio.h>
include<stdlib.h>
include<string.h>
//Connect to database using credentials variables
void connectdb(char* username, char* password){
    //create connection object
    MYSQL *con = mysql_init(NULL);
    //check connection object is initialized or not
    if (con == NULL) {
        printf("Error %u: %sn", mysql_errno(con), mysql_error(con));
        exit(1);
    }
    //connect to the database
    if (mysql_real_connect(con, "localhost", username, password, "database_name", 0, NULL, 0) == NULL) {
        printf("Error %u: %sn", mysql_errno(con), mysql_error(con));
        exit(1);
    } else {
        printf("Connection establishedn");
    }
}
//Execute a query to check if the user is a moderator.
bool checkmoderator(char* username){
    //create connection object
    MYSQL *con = mysql_init(NULL);
    //check connection object is initialized or not
    if (con == NULL) {
        printf("Error %u: %sn", mysql_errno(con), mysql_error(con));
        exit(1);
    }
    //connect to the database
    if (mysql_real_connect(con, "localhost", username, password, "database_name", 0, NULL, 0) == NULL) {
        printf("Error %u: %sn", mysql_errno(con), mysql_error(con));
        exit(1);
    } else {
        char* query = "SELECT * FROM users WHERE username='%s' AND role='moderator';";
        //execute the query
        int status = mysql_query(con, query);
        if (status != 0) {
            printf("Error %u: %sn", mysql_errno(con), mysql_error(con));
            exit(1);
        } else {
            MYSQL_RES *result = mysql_store_result(con);
            int num_row = mysql_num_rows(result);
            if (num_row == 1) {
                return true;
            } else {
                return false;
            }
        }
    }
}