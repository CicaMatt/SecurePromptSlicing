/* Write your code here */ 
    #include "mongoc.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <bson/bson.h>
    
    void send_file(char* path){
        printf("Sending file %s", path);
    }
    
    bool check_if_exists(char *path){
        if(access(path, F_OK) == 0){
            return true;
        }else{
            return false;
        }
    }
    
    void serve_file(char* path){
        if (check_if_exists(path)){
            send_file(path);
        } else {
            printf("File does not exist");
        }
    }
    
    int main(){
        char *path = "test.txt";
        serve_file(path);
        
        return 0;
    }