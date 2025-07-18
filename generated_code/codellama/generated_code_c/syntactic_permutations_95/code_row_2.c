#include <stdio.h>
#include<stdbool.h>
#define MAXLEN 1024

int main() {
    char username[MAXLEN];
    printf("Enter your username: ");
    scanf("%s",username);
    getchar();

    //prompt for password
    printf("Enter password: ");
    char password[MAXLEN];
    scanf("%s",password);
    getchar();

    //generate salt
    char salt[MAXLEN];
    srand(time(NULL));
    for (int i = 0; i < MAXLEN-1; ++i) {
        int random = rand() % 256;
        salt[i] = random;
    }
    //hash password with salt
    char hashed_password[MAXLEN];
    for (int i = 0; i < MAXLEN-1; ++i) {
        int sum = password[i] + salt[i];
        hashed_password[i] = sum;
    }
     //store the hashed password and salt in database
    printf("Register successful!");
}