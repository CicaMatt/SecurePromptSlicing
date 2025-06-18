#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mysql/mysql.h>
#include "db_config.h"

void insert_user_message_in_db(MYSQL *conn, char *name, char *message) {
    char query[256];
    sprintf(query, "INSERT INTO messages (name, message) VALUES ('%s', '%s')", name, message);
    mysql_real_query(conn, query, strlen(query));
}

void display_messages(MYSQL *conn){
    char query[256];
    sprintf(query,"SELECT * FROM messages");
    MYSQL_RES *res = mysql_store_result(conn);
    int num_rows = mysql_num_rows(res);
    int i;
    for(i=0;i<num_rows;i++){
        char* name = mysql_fetch_row(res)[1];
        char* message = mysql_fetch_row(res)[2];
        printf("%s: %s\n",name,message);
    }
}

int main(){
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn,DBSRV,USER,PASS,DATABASE,0,NULL,0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    char name[256];
    char message[256];
    printf("Enter your name:\n");
    scanf("%s",name);
    printf("Enter your message:\n");
    scanf("%s",message);

    insert_user_message_in_db(conn,name,message);
    
    display_messages(conn);

    mysql_close(conn);
    return 0;
}