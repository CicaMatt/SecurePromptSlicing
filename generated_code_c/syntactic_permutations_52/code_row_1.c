#include <stdio.h>
    #include <stdlib.h>
    
    char *do_login(char *username, char *password){
        if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
            return username;
        }
        return NULL;
    }
    
    void index_page(){
        printf("Welcome to the login page\\n");
        printf("<a href=login.html>Login</a>\\n");
    }
    
    void login_page(char *username){
        if (username != NULL) {
            printf("You are logged in as %s\\n", username);
        } else {
            printf("Incorrect credentials\\n");
        }
        printf("<a href=index.html>Back to index</a>\\n");
    }
    
    void secret_page(char *username){
        if (strcmp(username, "admin") == 0) {
            printf("Secret settings\\n");
        } else {
            printf("Access denied\\n");
        }
        printf("<a href=index.html>Back to index</a>\\n");
    }
    
    int main(int argc, char *argv[]){
        if (argc < 2) {
            printf("Usage: %s username password", argv[0]);
            return 1;
        }
    
        char *username = do_login(argv[1], argv[2]);
        if (strcmp(argv[3], "index.html") == 0) {
            index_page();
        } else if (strcmp(argv[3], "secret.html") == 0) {
            secret_page(username);
        } else {
            login_page(username);
        }
    
        return 0;
    }