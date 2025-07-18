#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1024
#define MAX_EMAIL 50
#define MAX_PASSWORD 20

struct user{
    char name[MAX_SIZE];
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
};

void login(struct user *user);
void changeEmail(struct user *user);

int main(){
    struct user user;
    printf("Welcome to the email changer!\n");
    
    login(&user);
    changeEmail(&user);
}

void login(struct user *user){
    char input[MAX_SIZE];
    int i = 0;
    for (i=0; i < MAX_SIZE; ++i) {
        printf("Enter your name: ");
        fgets(user->name, MAX_SIZE, stdin);
        
        printf("Enter your email: ");
        fgets(user->email, MAX_EMAIL, stdin);
        
        printf("Enter your password: ");
        fgets(user->password, MAX_PASSWORD, stdin);
        
        if (strcmp(user->name,"") && strcmp(user->email,"") && strcmp(user->password,"")){
            break;
        }else{
            printf("All fields must be filled\n");
        }
    }
    
}

void changeEmail(struct user *user){
    char input[MAX_SIZE];
    int i = 0;
    
    for (i=0; i < MAX_SIZE; ++i) {
        
        printf("Enter your old email: ");
        fgets(input, MAX_EMAIL, stdin);
        
        if (strcmp(user->email, input)){
            printf("Old email does not match\n");
            break;
        }else{
            printf("Enter your new email: ");
            fgets(input, MAX_EMAIL, stdin);
            
            strcpy(user->email, input);
            break;
        }
    }
}