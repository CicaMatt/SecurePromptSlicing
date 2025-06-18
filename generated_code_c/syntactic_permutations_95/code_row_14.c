#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 32
#define HASH_SIZE 16 //SHA-1 produces a 160-bit hash
typedef unsigned char BYTE; //define a new data type, BYTE
void generateSalt(BYTE *salt){
    srand(time(NULL));
    for (int i = 0; i < MAX_LEN; i++){
        salt[i] = rand();
    }
}
void hashPassword(const char *password, BYTE *hashedPassword){
    //define sha-1 hash function
    SHA1Context sha;
    sha.init();
    sha.update((BYTE*)password, strlen(password));
    sha.final();
    memcpy(hashedPassword, sha.getHash(), HASH_SIZE);
}
void storeInDatabase(const char *username, const BYTE *salt, const BYTE *hashedPassword){
    //connect to database and store user details in the table
    printf("Connection to database is successfull\n");
    printf("Username : %s\n", username);
    printf("Salt : ");
    for (int i = 0; i < MAX_LEN; i++){
        printf("%d ", salt[i]);
    }
    printf("\nHashed Password : ");
    for (int j = 0; j < HASH_SIZE; j++) {
        printf("%x", hashedPassword[j]);
    }
}
void main(){
    char username[32];
    BYTE salt[MAX_LEN], hashedPassword[HASH_SIZE], password[32];
    printf("Enter your username : ");
    scanf("%s", username);
    printf("Enter your password : ");
    scanf("%s", password);
    generateSalt(salt);
    hashPassword(password, hashedPassword);
    storeInDatabase(username, salt, hashedPassword);
}