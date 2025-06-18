#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* The following code is a simple login page that takes the username and password from the user 
and checks if they are correct. If they are, the user is redirected to the session page. 
If not, the user is told that the username or password is incorrect. */

int main() {
    char username[10];
    char password[10];
    printf("Username: ");
    scanf("%s", &username);
    printf("Password: ");
    scanf("%s", &password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        // Redirect to session page
        system("session.html");
    } else {
        printf("Username or password is incorrect.");
    }
    return 0;
}