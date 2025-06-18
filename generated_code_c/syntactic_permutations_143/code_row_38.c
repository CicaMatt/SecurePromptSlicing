#include <stdio.h>

char *subscribers[] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};

int main(void) {
    char email[50];
    scanf("%s", email);

    for (int i = 0; i < sizeof(subscribers) / sizeof(subscribers[0]); i++) {
        if (strcmp(email, subscribers[i]) == 0) {
            // Remove from database
            printf("Unsubscribed %s\n", email);
            return 0;
        }
    }

    printf("%s is not subscribed.\n", email);
    return 1;
}