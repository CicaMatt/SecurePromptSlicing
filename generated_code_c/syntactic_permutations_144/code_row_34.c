#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <mysql/mysql.h>

int checkEmail(char email[]);
void unsubscribe(char email[]);

int main(){
    char email[50];
    printf("Enter the email: ");
    scanf("%s", email); 
    int result = checkEmail(email);
    if (result == 1){
        unsubscribe(email);
        return 1;
    } else {
        return -1;
    }
}
int checkEmail(char email[]){
    MYSQL *conn; 
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "password";
    char *db = "emaildb"; 

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, db, 0, NULL, 0)) {
        printf("Error connecting to database:%s\n", mysql_error(conn));
        exit(1);
    }

    char qr[50] = "SELECT * FROM email WHERE email='";
    strcat(qr, email);
    strcat(qr, "'");

    if (mysql_query(conn, qr)) {
        printf("Error making query:%s\n", mysql_error(conn));
        exit(1); 
    }
    res = mysql_use_result(conn);
    int count=0;
    while ((row = mysql_fetch_row(res))) {
        count++;
    }
    if (count > 0){
        return 1;
    } else{
        return -1;
    }
}
void unsubscribe(char email[]){
    system("python3 /usr/local/bin/unsubscribe.py " + email);
}