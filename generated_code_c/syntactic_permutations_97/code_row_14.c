#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include <mysql/mysql.h>
void show_password(const char *str) {
    int i = 0;
    while (str[i] != '\0'){
        putchar('*');
        i++;
    }
}
int main() {
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "123456789"; /* set me first */
    char *database = "users";
    if (mysql_init(&mysql) == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }
    if (mysql_real_connect(&mysql, server, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: \n");
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return 2;
    }
     char *username;
     username = (char*)malloc(25*sizeof(char));
     printf("Enter a username: ");
     gets(username);
     if(strlen(username)<6){
         printf("Username should be at least 6 characters long");
         return 1;
    }
    char *password;
    password = (char*)malloc(25*sizeof(char));
    printf("Enter a password: ");
    gets(password);
    if(strlen(password)<8){
        printf("Password should be at least 8 characters long");
        return 1;
    }
    char *first_name;
    first_name = (char*)malloc(25*sizeof(char));
    printf("Enter a first name: ");
    gets(first_name);
    if(strlen(first_name)<4){
        printf("First name should be at least 4 characters long");
        return 1;
    }
     char *last_name;
    last_name = (char*)malloc(25*sizeof(char));
    printf("Enter a last name: ");
    gets(last_name);
    if(strlen(last_name)<4){
        printf("Last name should be at least 4 characters long");
        return 1;
    }
     char *hashed_password = (char*)malloc(25*sizeof(char));
    sprintf(hashed_password, "%d", password);
    int len = strlen(hashed_password);
    for(int i=0; i<len; i++){
        if(!isalpha(hashed_password[i])){
            hashed_password[i] = '*';
        }
    }
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s'", username);
    if (mysql_query(&mysql, query) != 0) {
        fprintf(stderr, "mysql_query() failed: \n");
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return 3;
    }
    res = mysql_store_result(&mysql);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: \n");
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return 3;
    }
    int numrows = mysql_num_rows(res);
    if (numrows > 0) {
        printf("Username already exists.\n");
        return 1;
    } else {
        sprintf(query, "INSERT INTO users VALUES('%s', '%s', '%s','%s')", username, hashed_password, first_name, last_name);
        if (mysql_query(&mysql, query) != 0) {
            fprintf(stderr, "mysql_query() failed: \n");
            fprintf(stderr, "%s\n", mysql_error(&mysql));
            return 3;
        }
        printf("Registration successful! %s is registered with password %s \n", username, hashed_password);
    }
    mysql_free_result(res);
    mysql_close(&mysql);
    return 0;
}