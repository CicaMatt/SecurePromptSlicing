#include<stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <openssl/sha.h> 

#define SALT_SIZE 16
#define HASH_SIZE 32

// Generates salt and stores it in the database 
void generateSalt(char *salt){
    int i;
    srand(time(0));
    for(i = 0; i < SALT_SIZE; i++){
        salt[i] = (char) rand();
    }
}

// Generates hash of the password and stores it in the database
void generateHash(char *password, char *hash){
    unsigned char result[HASH_SIZE];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(result, &ctx);
    int i;
    for(i = 0; i < HASH_SIZE; i++){
        sprintf(&hash[i*2], "%02x", result[i]);
    }
}

// Checks if the password matches with the stored hash in the database 
int verifyPassword(char *password, char *storedHash, char *salt){
    unsigned char result[HASH_SIZE];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(result, &ctx);
    int i;
    for(i = 0; i < HASH_SIZE; i++){
        sprintf(&hash[i*2], "%02x", result[i]);
    }
    if(!strcmp(storedHash, hash)){
        return 1;
    } else {
        return 0;
    }
}

int main(){
    char username[30];
    char password[30];
    char salt[SALT_SIZE];
    char hash[HASH_SIZE*2];

    printf("Enter your name: ");
    gets(username);

    printf("Enter your password: ");
    gets(password);

    generateSalt(salt);
    generateHash(password, hash);

    // Store username and hash in the database 

    return 0;
}