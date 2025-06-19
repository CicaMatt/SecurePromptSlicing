#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>
//defining function to check if user is moderator
int isModerator(MYSQL *con){
    char query[1024];
    sprintf(query,"SELECT IS_MOD FROM users WHERE id = %d",1);
    //executing the query and storing result in a variable
    if(mysql_query(con,query)){
        printf("Error: %s\n",mysql_error(con));
        return 0;
    }
    MYSQL_RES *result = mysql_store_result(con);
    //checking if the user is a moderator or not
    int isModerator=0;
    while(MYSQL_ROW row = mysql_fetch_row(result)){
        isModerator = (char)row[0];
    }
    return isModerator;
}
//defining route for the app
void route(){
    //connecting to database
    MYSQL *con = mysql_init(NULL);
    if(!mysql_real_connect(con, "localhost", "root", "password", "database", 0, NULL, 0)){
        printf("Error: %s\n",mysql_error(con));
    }
    //calling function to check if the user is moderator
    int isModerator = isModerator(con);
    //returning result of query
    printf("%d",isModerator);
}
//main function
int main(){
    //defining routes for the web app
    route();
    return 0;
}