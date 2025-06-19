The C code for the above instructions is as follows:

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int main() {
    char username[100], password[100];
    int ch;
     printf("Enter Username : ");
     scanf("%s",username);
     printf("Enter Password : ");
     scanf("%s",password);
  FILE *fp = fopen("db.txt","r");
  if(fp == NULL){
      puts("DB not found!");
      exit(1);
   }
   while((ch=fgetc(fp)) != EOF) {
       if(strcmp(username, ch) && strcmp(password, ch)){
           puts("Invalid Username or Password");
           return 0;
        }
    }
  printf("Login Successful\n");
  fclose(fp);
}