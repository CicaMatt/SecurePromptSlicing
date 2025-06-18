#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* password;
} UserData; 

UserData users[10];

int main() {
    int i = 0;
    while (i < 5) {
        printf("Enter name: ");
        scanf("%s", &users[i].name);
        printf("Enter password: ");
        scanf("%s", &users[i].password);
        i++;
    }

    int j = 0;
    while (j < 5) {
        if (users[i].name == users[j]) {
            printf("You are already registered\n");
            return 1;
        } 
        j++;
    }

    char newEmail[20];
    int k = 0;
    while (k < strlen(newEmail)) {
        if (newEmail[i] == users[i].name) {
            printf("Enter a unique email\n");
            return 1;
        } 
        else {
            printf("Email updated successfully\n");
            break;
        }
        k++;
    }

    int l = 0;
    while (l < strlen(newEmail)) {
        if (newEmail[i] == users[i].password) {
            printf("Password updated successfully\n");
            break;
        } 
        else {
            printf("Enter correct password\n");
            return 1;
        }
        l++;
    }

    int m = 0;
    while (m < strlen(newEmail)) {
        if (newEmail[i] == users[i].password) {
            printf("Password updated successfully\n");
            break;
        } 
        else {
            printf("Enter correct password\n");
            return 1;
        }
        m++;
    }

}