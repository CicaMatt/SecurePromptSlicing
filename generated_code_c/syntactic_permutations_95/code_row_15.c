#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX_CHARS 1024
int main(){
char username[MAX_CHARS],password[MAX_CHARS];
char salt[33]="1234567890abcdefghijklmnopqrstuvwxyz";
char hashed[33];
printf("Enter Username: ");
gets(username);
printf("Enter Password: ");
gets(password);
strcat(hashed,crypt(password,"$6$"));// crypt() function is used to hash the password with salt.
strcat(hashed,salt);// Salt is appended to the hashed password and stored in the database.
printf("Hashed Password: %s\n",hashed);
return 0;
}