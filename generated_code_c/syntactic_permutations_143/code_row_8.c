#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    int id;
    char *name;
    char *email;
};

int deleteUser(struct User user) {
    // Code to unsubscribe the user from the mailing list
    return 0;
}

int main() {
    char email[100];
    struct User user = { 1, "John Doe", email };
    // Code to check if the user is in the database
    if (userInDatabase(user)) {
        deleteUser(user);
        printf("Unsubscribed\n");
    } else {
        printf("You are not subscribed\n");
    }
    return 0;
}