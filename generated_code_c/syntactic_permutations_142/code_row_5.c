#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024

// function to check if email address is in database or not
int unsubscribe(char *email){
    // connect to database
    char query[MAX_SIZE];
    sprintf(query, "SELECT * FROM subscribers WHERE email='%s'", email);
    int result = 0;
    if (mysql_query(conn, query)){
        printf("Error: %s\n", mysql_error(conn));
    } else {
        MYSQL_RES *res = mysql_store_result(conn);
        if (res != NULL){
            result = 1;
            // remove email address from database
            sprintf(query, "DELETE FROM subscribers WHERE email='%s'", email);
            if (mysql_query(conn, query)){
                printf("Error: %s\n", mysql_error(conn));
            }
        }
    }
    return result;
}

int main(){
    // ask user for email address
    char email[MAX_SIZE];
    printf("Enter your email address: ");
    scanf("%s", email);
    if (unsubscribe(email)){
        printf("You have been unsubscribed from our mailing list\n");
    } else {
        printf("Error: Email address not found in database\n");
    }
}