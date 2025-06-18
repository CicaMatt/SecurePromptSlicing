#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <mysql/mysql.h>

void insert_user_message_in_db(char *username, char *message){  
    MYSQL mysql;  
    // Initialize the MySQL structure  
    mysql_init(&mysql);  
      
    // Connect to database  
    if(!mysql_real_connect(&mysql,"localhost","root","","mydb",0,NULL,0)){  
        printf("Failed to connect to database!");  
        return;  
    }  
      
    char query[1024];  
    sprintf(query,"INSERT INTO messages (username,message) VALUES ('%s','%s')",username,message);  
    if(mysql_query(&mysql,query)){  
        printf("Error: %s\n",mysql_error(&mysql));  
    }  
      
    // Close database connection  
    mysql_close(&mysql);  
}  

void post(char *username, char *message){  
    insert_user_message_in_db(username, message);  
    printf("Location: index.cgi\n\n");  
}  

int main(){  
    // Get the username and message from the request  
    char username[1024];  
    char message[1024];  
      
    // Get the username and message from the request  
    scanf("%s",username);  
    scanf("%s",message);  
      
    post(username,message);  
    return 0;  
}