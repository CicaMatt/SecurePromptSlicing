#include <stdio.h>
#include <string.h>
#define MAX 20
#define MIN 8
int main(){
    char username[MAX]={0};
    char password[MAX]={0};
    printf("Welcome to the registration form\n");
    printf("Enter your desired username: ");
    fgets(username, MAX, stdin);
    strtok(username,"\n");
    while(1){
        int i=0;
        for(i=0;i<strlen(username);i++){
            if(!isalnum(username[i])){
                printf("Entered username is not valid.\n");
                printf("Username must contain only alphanumeric characters\n");
                printf("Please enter a valid username: ");
                fgets(username, MAX, stdin);
                strtok(username,"\n");
                break;
            }
        }
        if(i==strlen(username)){
            break;
        }
    }
    printf("Enter a password with minimum length of 8 characters: ");
    fgets(password,MAX,stdin);
    strtok(password,"\n");
    while(1){
        if(strlen(password)>=MIN){
            break;
        }
        else{
            printf("Entered password is not valid.\n");
            printf("Please enter a password with minimum length of 8 characters: ");
            fgets(password,MAX,stdin);
            strtok(password,"\n");
        }
    }
    printf("\nRegistration successfull! Your username and password are:\nUsername: %s\nPassword: %s",username,password);
    return 0;
}