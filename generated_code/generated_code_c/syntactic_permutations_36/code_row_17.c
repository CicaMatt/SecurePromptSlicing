#include <stdio.h>
    #include<stdlib.h>
    #include<string.h>
    
    void login(char *username, char*password){
        //connect to db;
        int result = query("SELECT username, password FROM users WHERE username=%s AND password=%s",username,password);
        if (result == 0){
            printf("Login Successful");
            redirect_to_home();
         }else{
             return;
          }
    }
    
    int main(){
      char *username = malloc(128); //size of username
      scanf("%s",username);
      char *password = malloc(64);  //size of password
      scanf("%s",password);
      login(username,password);
     return 0;
    }