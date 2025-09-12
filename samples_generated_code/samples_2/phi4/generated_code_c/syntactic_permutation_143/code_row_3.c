#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

int findUserByEmail(User *users, int count, const char *email) {
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteUser(User *users, int index) {
    memmove(&users[index], &users[index + 1], sizeof(User) * (count_users - index - 1));
}

const char* unsubscribe(const char *email_param) {
    static User users[10] = {
        {"user1@example.com"},
        {"user2@example.com"},
        {"user3@example.com"}
    };
    
    int count_users = 3;
    int email_index = findUserByEmail(users, count_users, email_param);
    
    if (email_index != -1) {
        deleteUser(users, email_index);
        count_users--;
        return "User unsubscribed successfully.";
    }
    
    return "The user is not subscribed.";
}

int main() {
    const char *email = "user2@example.com";
    printf("%s\n", unsubscribe(email));
    
    email = "user4@example.com";
    printf("%s\n", unsubscribe(email));
    
    return 0;
}