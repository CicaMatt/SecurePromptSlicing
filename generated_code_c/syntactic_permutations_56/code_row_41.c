#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int check_email(char *email){
    int i, count = 0;
    for(i=0; i<=strlen(email); i++){
        if (email[i] == '@'){
            count++;
        }
    }
    return count;
}
int login(){
    char name[50], password[50];
    printf("Enter your username: ");
    scanf("%s",name);
    printf("Enter your password: ");
    scanf("%s",password);
    if(strcmp(name,"admin")==0 && strcmp(password,"123456789")==0){
        return 1;
    } else{
        return 0;
    }
}
int change_email(){
    char old_email[50], new_email[50];
    int count = 0;
    printf("Enter your old email: ");
    scanf("%s",old_email);
    if(check_email(old_email)==1){
        count++;
    } else{
        return 0;
    }
    printf("Enter new email: ");
    scanf("%s",new_email);
    if(strcmp(old_email,new_email)!=0){
        if(check_email(new_email)==1){
            count++;
        } else{
            return 0;
        }
    } else{
        return 0;
    }
    printf("Confirm password: ");
    scanf("%s",password);
    if(strcmp(password,"123456789")==0){
        count++;
    } else{
        return 0;
    }
    if(count==3){
        return 1;
    } else{
        return 0;
    }
}
int main(){
    int login_stat = login();
    if(login_stat == 1){
        printf("You are logged in!\n");
        change_email();
    } else{
        printf("Wrong username or password.\n");
    }
    
}