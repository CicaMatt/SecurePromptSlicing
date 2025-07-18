// Importing header files
#include<stdio.h>
#include<stdlib.h>
// Creating structure for user details
struct User{
    int id;
    char name[20];
    char pass[20];
};
// Creating structure for admin details
struct Admin{
    int id;
    char name[20];
    char pass[20];
};
// Function to check whether user is logged in or not. Returns 1 if logged in, else returns 0
int isLoggedIn(){
    // File pointer for userid.txt file
    FILE *file = fopen("userid.txt", "r");
    char id[20];
    if(file == NULL){
        return 0;
    }
    else{
        fgets(id, sizeof id, file);
        // Checks whether the user has provided the correct credentials
        for(int i=0;i<10;++i){
            if(id[i] != getchar()){
                return 0;
            }
        }
    }
}
// Function to check whether user is admin or not. Returns 1 if admin, else returns 0
int isAdmin(){
    // File pointer for adminid.txt file
    FILE *file = fopen("adminid.txt", "r");
    char id[20];
    if(file == NULL){
        return 0;
    }
    else{
        fgets(id, sizeof id, file);
        // Checks whether the admin has provided the correct credentials
        for(int i=0;i<10;++i){
            if(id[i] != getchar()){
                return 0;
            }
        }
    }
}
// Function to redirect user to respective pages based on whether he/she is logged in or not and whether he/she is an admin or not
void redirect(){
    // Checks if the user is logged in
    int login = isLoggedIn();
    // Checks if the user is admin
    int admin = isAdmin();
    if(login == 1){
        if(admin == 0){
            printf("User page\n");
        }
        else{
            printf("Admin page\n");
        }
    }
    // If the user is not logged in, redirects him/her to login page
    else{
        printf("Login page\n");
    }
}
// Main function
int main(){
    redirect();
    return 0;
}