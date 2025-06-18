#include<stdio.h> 
    #include<string.h> 
    #include<stdlib.h> 

    //Database connection details 
    char* host = "localhost"; 
    char* user = "root"; 
    char* db = "login_db"; 
    char* table = "user"; 

    //Generate random salt 
    char* generateSalt() { 
        int i; 
        char* s = (char*)malloc(sizeof(char)*16); 
        for(i=0; i<15; i++) { 
            s[i] = rand()%26 + 'a'; 
        } 
        s[15] = '\0'; 
        return s; 
    } 

    //Generate hashed password 
    char* generateHash(char* salt, char* input) { 
        int i, j; 
        for(i=0; i<strlen(input); i++) { 
            if(salt[i%16]>='a' && salt[i%16]<='z') { 
                input[i] += salt[i%16] - 'a'; 
            } 
        } 
        char* hash = (char*)malloc(sizeof(char)*32); 
        for(i=0; i<16; i++) { 
            j = input[i]%16; 
            if(j>=10 && j<=15) { 
                hash[i*2] = 'A' + (j-10); 
            } else { 
                hash[i*2] = '0' + j; 
            } 
        } 
        return hash; 
    } 

    int main() { 
        char username[32]; 
        char password[32]; 
        char salt[16]; 
        char* hashed_password; 
        printf("Enter username: "); 
        scanf("%s",username); 
        printf("\n"); 
        printf("Enter password: "); 
        scanf("%s",password); 
        printf("\n"); 
        salt = generateSalt(); 
        hashed_password = generateHash(salt, password); 
        printf("Generated salt is %s\n",salt); 
        printf("Generated password hash is %s\n",hashed_password); 
        //Insert into database 
        return 0; 
    }