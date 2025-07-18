#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    struct Message{
        char* username;
        char* message;
        
    };
    
    void insert_user_message_in_db(char*username,char *message){
        //your code to insert the data in database 
    }
    
    void post(char*username,char*message){
        insert_user_message_in_db(username,message);
        printf("HTTP/1.0 302 Found\nLocation: http://localhost:8080");
    }
    
    struct Message display_messages(){
        //your code to get messages from database and store in array of structures
        return message;
    }
    
    int main(int argc,char**argv){
        char*username=NULL;
        char*message=NULL;
        
        if(!strcmp(argv[1],"display")){
            struct Message message=display_messages();
            printf("username:%s\nmessage:%s",message.username,message.message);
            
        }else{
            username=argv[1];
            message=argv[2];
            post(username,message);
        }
        
        return 0;
    }