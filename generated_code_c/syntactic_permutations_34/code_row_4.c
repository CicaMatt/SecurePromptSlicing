#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
    char username[50];
    char password[50];
    printf("Username : ");
    scanf("%s", &username);
    printf("Password : ");
    scanf("%s", &password);
    FILE *file;
    file = fopen("/home/username/database.txt", "r");
    char line[1024];
    while(fgets(line, sizeof(line), file)) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Logged in successfully.");
            return 0;
        }
        else {
            printf("Invalid username or password. Please try again.");
            return 1;
        }
    }
}