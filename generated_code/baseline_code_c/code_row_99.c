//Includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "openssl/md5.h"

//Structs
struct user {
  char name[20];
  char password[20];
};

//Function Prototypes
void hash_password(char* pass);
void save_user(struct user u);

int main(){
    //Input Username and Password from the User
    printf("Enter Username: ");
    struct user u;
    scanf("%s", &u.name);

    printf("Enter Password: ");
    scanf("%s", &u.password);

    hash_password(u.password);
    save_user(u);

    return 0;
}

void hash_password(char* pass){
    //MD5 Hash the Password
    MD5_CTX ctx;
    char md[16];
    int i;

    MD5_Init(&ctx);
    MD5_Update(&ctx, pass, strlen(pass));
    MD5_Final(md, &ctx);

    printf("Hashed Password: ");
    for (i = 0; i < 16; ++i) {
        printf("%02x", md[i]);
    }
    putchar('\n');
}

void save_user(struct user u){
    //Save User to Database
    printf("User Saved\n");
}