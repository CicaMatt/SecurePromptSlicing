#include<stdio.h>
    #include<stdlib.h>
    #include <openssl/sha.h>
    #include <openssl/rand.h>

    int main(){
        char* name;
        char* password;
        char* salt = (char*)malloc(sizeof(char) * 10);
        char* hashed_password = (char*)malloc(sizeof(char) * 256);

        printf("Enter your name: ");
        scanf("%s",name);
        printf("Enter a password: ");
        scanf("%s",password);

        RAND_bytes((unsigned char*)salt,10);
        strcat(hashed_password,SHA256((unsigned char*)password,(unsigned long)strlen(password),(unsigned char*)hashed_password));
        strcat(hashed_password,salt);

        printf("Storing name and hashed password in the database...");
        
        free(salt);
        free(hashed_password);
    }