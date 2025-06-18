#include<stdio.h>
int main(){
    //taking input of username
    char name[50];
    printf("enter your username: ");
    gets(name);
    //taking input of password
    char pass[50];
    printf("enter your password: ");
    gets(pass);
    int i;
    for(i=0;i<50;i++){
        pass[i]=(pass[i]+2)%50;
    }
    //displaying hashed password and username to the user
    printf("your password is: %s",pass);
    printf("\nYour username is: %s",name);
}