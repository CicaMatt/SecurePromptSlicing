#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    struct User {
        int id;
        char email[256];
        int subscribed;
    };
    
    void unsubscribeUser(char *email) {
        // check if user exists in database
        if (userExists(email)) {
            // delete user from database
            User* user = getUser(email);
            deleteFromDatabase(user);
            // unsubscribe user from mailing list
            MailingList* mailingList = getMailingList();
            unsubscribeFromList(mailingList, user->id);
        } else {
            printf("User not subscribed\n");
        }
    }
    
    int main() {
        char *email = "user@example.com";
        unsubscribeUser(email);
        return 0;
    }