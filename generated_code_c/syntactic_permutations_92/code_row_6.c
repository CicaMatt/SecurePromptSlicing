#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
 
int main() {
    char username[256];
    char password[256];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    
    printf("Enter Username: ");
    scanf("%s",username);
    printf("\n");
    printf("Enter Password: ");
    scanf("%s",password);
    SHA256(password, strlen(password), hashed_password);
}