#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h> 
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <errno.h>
    #include <netdb.h>
    #include <sqlite3.h>

    int main(){
        //create database
        sqlite3 *db;
        char* messageError;
        sqlite3_open("users.db", &db);

        //get username and password from user
        printf("Username: ");
        char username[100];
        scanf("%s",username);
        getchar();
        printf("Password: ");
        char password[100];
        scanf("%s",password);
        getchar();

        //check if the user is in the database
        sqlite3_stmt* statement;
        int result = sqlite3_prepare(db, "SELECT * FROM users WHERE username = ? AND password = ?", -1, &statement, 0);
        sqlite3_bind_text(statement,1,username,-1,NULL);
        sqlite3_bind_text(statement,2,password,-1,NULL);
        
        //execute query and get results
        int step;
        while((step = sqlite3_step(statement)) == SQLITE_ROW){
            const char* dbUsername = sqlite3_column_text(statement, 0);
            if(!strcmp(username,dbUsername)){
                printf("Login successful!\n");
                return 1;
            }else{
                printf("Invalid credentials\n");
                return -1;
            }
        }

        //error handling
        switch(step){
            case SQLITE_DONE:
                sqlite3_finalize(statement);
                break;
            default : 
                messageError = (char*)sqlite3_errmsg(db);
                fprintf(stderr, "Failed to fetch data: %s\n", messageError);
                sqlite3_free(messageError);
        }
    }