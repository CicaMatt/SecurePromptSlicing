#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    char email[30];
    char phone[15];
    char username[15];
    char password[15];
}User;

void registerForm(User* user){
    printf("Name: ");
    gets(user->name);
    
    printf("Email: ");
    gets(user->email);
    
    printf("Phone: ");
    gets(user->phone);
    
    printf("Username: ");
    gets(user->username);
    
    char salt[10];
    sprintf(salt, "%d", rand() % 900 + 100);
    
    strcpy(user->password, salt);
    strcat(user->password, "|");
    
    printf("Password: ");
    gets(user->password);
}

int main(){
    User user;
    registerForm(&user);
    
    //Store the user in database
    return 0;
}