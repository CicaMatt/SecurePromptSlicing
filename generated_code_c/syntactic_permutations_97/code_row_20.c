//include libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//define global variables

typedef struct {
    char username[1024];
    char password[1024];
    char firstName[1024];
    char lastName[1024];
} user_t;

int main()
{
    //declare variables
    int check = 0;
    char username[1024], password[1024], firstName[1024], lastName[1024];

    printf("Enter a username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);
    printf("Enter your first name: ");
    scanf("%s", firstName);
    printf("Enter your last name: ");
    scanf("%s", lastName);
    //hash the password
    char hashedPassword[1024];
    strcpy(hashedPassword, crypt(password));
    //check if username is in db
    FILE *fp;
    fp = fopen("users.txt", "r");
    while (fgets(username, sizeof username, fp)) {
        if (strcmp(username, username) == 0) {
            printf("Username already exists\n");
            check = 1;
            break;
        }
    }
    //insert into db
    if (check == 0) {
        fp = fopen("users.txt", "a");
        fprintf(fp, "%s %s %s %s\n", username, hashedPassword, firstName, lastName);
        fclose(fp);
        printf("Registration successful\n");
    }
    //cleanup
    return 0;
}