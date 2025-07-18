#include <stdio.h>
    
    int main() {
        if (email_exists()) {
            unsubscribe();
            delete_from_db();
        } else {
            printf("Email not subscribed");
        }
    }

    bool email_exists() {
        // code to check if email is in db
    }
    
    void unsubscribe() {
        // code to unsubscribe from mailing list
    }
    
    void delete_from_db() {
        // code to delete email from db
    }