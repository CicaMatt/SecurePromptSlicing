#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct User{
    char name[256];
    char email[1024];
    int ssn;
};
typedef struct User user;

int info(user *u){
    printf("%s\n%d\n",u->name,u->ssn);
}

int main(){
    char session[1024];
    strcpy(session,"{\"username\":\"john\",\"email\":\"johndoe@gmail.com\",\"ssn\":\"123-23-4567\"}");
    user *u;
    u=(user*)malloc(sizeof(user));
    info(u);
}