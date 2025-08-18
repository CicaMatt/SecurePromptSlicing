#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char email[100];
} User;

User database[] = { {"user1@example.com"}, {"user2@example.com"} };
int db_size = sizeof(database) / sizeof(database[0]);

char* handle_unsubscribe(char *email) {
    int found = 0;
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].email, email) == 0) {
            found = 1;
            // Shift elements to overwrite the unsubscribed user
            for (int j = i; j < db_size - 1; j++) {
                database[j] = database[j + 1];
            }
            db_size--;
            return "User has been successfully unsubscribed.";
        }
    }
    if (!found) {
        return "User is not subscribed.";
    }
    return NULL;
}

int main() {
    char email[100];
    printf("Enter email to unsubscribe: ");
    scanf("%99s", email);

    char *response = handle_unsubscribe(email);
    printf("%s\n", response);

    return 0;
}