#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <sys/stat.h>

int unsubscribe(const char *email);
void get_email(char* email);

int main(){
    char email[1024];
    get_email(email);
    return unsubscribe(email);
}

//Function to check if email is in database and remove it if so, otherwise print error message.
int unsubscribe(const char *email){
    //Setup connection information for the database. 
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    //Set information for the database.
    conn = mysql_real_connect(conn, "localhost", "user", "password", "dbname", 0, NULL, 0);
    if (conn == NULL) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    //Set the query to check if email is in database.
    char *sql = "SELECT email FROM subscribers WHERE email = ?";
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    //Bind email to the query.
    MYSQL_BIND bind[1];
    char buffer[256];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)email;
    bind[0].is_null = 0;
    if (mysql_stmt_bind_param(stmt, bind)) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    //Execute the query.
    if (mysql_stmt_execute(stmt)) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    //Get results of the query.
    MYSQL_RES *result = mysql_store_result(stmt);
    int num_rows = mysql_num_rows(result);

    //If email is in database, remove it and print success message. 
    if (num_rows > 0) {
        char *sql2 = "DELETE FROM subscribers WHERE email = ?";
        MYSQL_STMT *stmt2;
        stmt2 = mysql_stmt_init(conn);
        if (mysql_stmt_prepare(stmt2, sql2, strlen(sql2)) != 0) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }

        //Bind email to the query.
        MYSQL_BIND bind2[1];
        memset(bind2, 0, sizeof(bind2));
        bind2[0].buffer_type = MYSQL_TYPE_STRING;
        bind2[0].buffer = (char *)email;
        bind2[0].is_null = 0;
        if (mysql_stmt_bind_param(stmt, bind2)) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }

        //Execute the query.
        if (mysql_stmt_execute(stmt2)) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }

        printf("Unsubscribed successfully.\n");
    }

    //If email is not in database, print error message.
    else {
        printf("Email does not exist in the database.\n");
    }
}

//Function to get user's email address from input.
void get_email(char* email){
    char buffer[1024];
    printf("Enter your email address:\n");
    fgets(buffer, 1023, stdin);
    sscanf(buffer, "%s", email);
}