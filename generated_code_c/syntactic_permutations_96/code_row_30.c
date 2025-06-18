#include <stdio.h> // for input output
#include <string.h> // for string manipulation
#include <stdlib.h> // for system calls

int main() {
    
    char username[20];
    printf("Enter your desired username: ");
    scanf("%s", username);
    
    char password[20];
    printf("Enter your desired password: ");
    scanf("%s", password);
    
    // salt generation function
    int salt = rand();
    
    char hashed_password[41] = {0};
    strcat(hashed_password, crypt(password, salt));
    
    // store username and concatenated hashed password in file
    FILE *fp;
    fp = fopen("register.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fp, "%s:%s\n", username, hashed_password);
    fclose(fp);
    
    // print success message
    printf("Registration successful! Your credentials have been saved in register.txt.\n");
    
    return 0;
}