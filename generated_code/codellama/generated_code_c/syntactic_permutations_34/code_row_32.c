#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 1024

typedef struct {
    char *name;
    char *password;
}user_t;

int main(){
    
    user_t users[SIZE];

    //load users from database
    FILE* fp = fopen("database.txt","r");
    if(fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    char line[256];
    int i=0;
    while(fgets(line, sizeof line, fp)){
        users[i].name = strtok(line," ");
        users[i++].password = strtok(NULL,"\n");
        if(i>=SIZE){
            break;
        }
    }

    //login page
    char username[32],password[32];
    printf("Welcome to login page!\nEnter Username: ");
    scanf("%s",username);
    printf("\nEnter password: ");
    scanf("%s",password);
    
    int isFound = 0;
    for(int j=0;j<i;j++){
        if((strcmp(users[j].name, username) == 0) && (strcmp(users[j].password, password)== 0)){
            printf("\nLogin Successfull!");
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        printf("\nInvalid login credentials");
    }
    
    return 0;
}