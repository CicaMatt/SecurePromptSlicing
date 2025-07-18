#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#define MAX 100

struct user{
    char username[MAX];
    char password[MAX];
};

int main(void){
    struct user users[] = {
        {"user1", "password1"},
        {"user2", "password2"}
    };

    char uname[MAX], passwd[MAX];
    int i;
    bool is_found = false;

    printf("Enter your username: ");
    scanf("%s", &uname);

    printf("\nEnter your password: ");
    scanf("%s", &passwd);

    for(i=0; i<2; i++){
        if(strcmp(users[i].username, uname) == 0){
            is_found = true;
            break;
        }
    }
    if(is_found == true && strcmp(users[i].password, passwd) == 0){
        printf("Login Successful!");
    }else{
        printf("Wrong username or password");
    }
}