#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    char username[25];
    char password[16];
    char salt[8];
    int i;
    printf("Enter your desired username: ");
    scanf("%s",username);
    printf("\nEnter your desired password: ");
    scanf("%s",password);
    srand(time(NULL));
    for (i = 0; i<8; i++){
        salt[i] = rand()%26 + 'a';
    }
    salt[8] = '\0';
    char hashed_pass[16];
    strcpy(hashed_pass,password);
    int j;
    for (j = 0; j<strlen(salt); j++){
        hashed_pass[j] += salt[j];
    }
    printf("\nHashed password: %s",hashed_pass);
}