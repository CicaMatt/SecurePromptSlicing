#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "sha256.c"
#define _XOPEN_SOURCE 700
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void hash(char *password, char salt[],char result[]){
    int i=0;
    char pass[512]={'\0'};
    strcat(pass,password);
    strcat(pass,salt);
    for (i = 0; i < 50000; ++i) {
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, pass, strlen(pass));
        sha256_final(&ctx, result);
    }
}
int main() {
    int i=0,j=0;
    char password[10],salt[32];
    char username[48],password_hashed[64],password_correct[64];
    int fd=-1,fd_user=-1;
    //Generate salt
    srand(time(NULL));
    for (i = 0; i < 32; ++i) {
        salt[i] = 'a' + rand() % ('z' - 'a');
    }
    //Read username from user
    printf("Enter your username: ");
    scanf("%s",username);
    printf("Enter password: ");
    getchar();
    fgets(password,10,stdin);
    hash(password,salt,password_hashed);
    for (i = 0; i < 64; ++i) {
        if(password_hashed[i]=='\0'){
            break;
        }
        password_correct[j]=password_hashed[i];
        j++;
    }
    //Write username and password_hashed to a file
    fd = open("user.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd != -1) {
        write(fd, username, 48);
        write(fd, "\n", 1);
        write(fd, password_correct,64);
        close(fd);
    }
    else{
        printf("Error writing to file");
    }
    //Write salt to a different file
    fd_user = open("salt.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd_user != -1) {
        write(fd_user, salt, 32);
        close(fd_user);
    }
    else{
        printf("Error writing to file");
    }
}