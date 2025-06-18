#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *generate_salt(int length) {
    char *salt = (char*)malloc(sizeof(char)*length);
    srand(time(0));
    for(int i=0;i<length;i++){
        salt[i]=(char)(33+rand()%94);
    }
    return salt;
}

char *hash_password(const char* password, const char *salt) {
    int length = strlen(password)+strlen(salt);
    char *new_password = malloc(sizeof(char)*length);
    for(int i=0;i<strlen(password);i++){
        new_password[i]=(char)(password[i]+salt[i]);
    }
    return new_password;
}

void register() {
    char username[128];
    char password[128];
    int length = 8;
    char *salt = generate_salt(length);
    printf("Enter username: ");
    scanf("%s",username);
    printf("Enter password: ");
    scanf("%s",password);
    char *hashed_password= hash_password(password,salt);
    char *final = (char*)malloc(sizeof(char)*strlen(hashed_password)+length+1);
    strcpy(final,hashed_password);
    strcat(final,salt);
    printf("Username: %s\n",username);
    printf("Hashed Password: %s\n",final);
}

int main() {
    register();
    return 0;
}