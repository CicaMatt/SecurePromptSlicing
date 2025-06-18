#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <openssl/evp.h>

void gen_hash(char* message, char* hash){
    int len = strlen(message);
    unsigned char *md;
    md = (unsigned char*)malloc(EVP_MAX_MD_SIZE);
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit(ctx, EVP_sha256());
    EVP_DigestUpdate(ctx, message, len);
    EVP_DigestFinal(ctx, md, NULL);
    int i;
    for (i = 0; i < 32; i++){
        sprintf(&hash[i*2], "%02x", md[i]);
    }
}

int check_username(char* username){
    //check if the username exists in the database
    //return 1 if it does not exist
    //return 0 if it does exist
    return 1;
}

void register_user(char* username, char* password){
    //insert username and hashed password into database
}
int main(){
    int len = 0;
    char username[256];
    char password[256];
    char hash[64];
    printf("Enter the username: ");
    scanf("%s", &username);
    printf("Enter the password: ");
    scanf("%s", &password);
    len = strlen(password);
    gen_hash(password, hash);
    if(check_username(username)){
        register_user(username, hash);
        printf("Registration succeeded");
    } else {
        printf("Username already exists");
    }

}