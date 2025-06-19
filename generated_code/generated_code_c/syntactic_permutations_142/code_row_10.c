#include <stdio.h>
    #include <string.h>

    struct {
        char *email;
        int is_subscribed;
    } subscribers[] = { 
        {"john@example.com", 1}, 
        {"mark@example.com", 0}, 
        {"lucy@example.com", 1}
    };

    void unsubscribe(char *email) {
        int i, found = 0;
        for (i = 0; i < sizeof(subscribers) / sizeof(subscribers[0]); i++) {
            if (!strcmp(subscribers[i].email, email)) {
                found = 1;
                subscribers[i].is_subscribed = 0;
                break;
            }
        }

        if (found) {
            printf("You have been unsubscribed.\n");
        } else {
            printf("You are not in the database.\n");
        }
    }

    int main() {
        char email[1024];

        printf("Enter your email address: ");
        fgets(email, sizeof(email), stdin);

        unsubscribe(email);

        return 0;
    }