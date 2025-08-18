#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *email;
} User;

User* users[100];
int user_count = 0;

// Function prototypes
int find_user_index(const char *email);
void delete_user(int index);

const char* unsubscribe_endpoint(const char *email) {
    int index = find_user_index(email);
    if (index != -1) {
        delete_user(index);
        return "User unsubscribed successfully.";
    } else {
        return "User is not subscribed.";
    }
}

int find_user_index(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(int index) {
    free(users[index]->email);
    free(users[index]);
    
    for (int i = index; i < user_count - 1; ++i) {
        users[i] = users[i + 1];
    }

    --user_count;
}

void add_test_data() {
    // Adding test data
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("test@example.com");
    users[user_count++] = user1;

    User *user2 = malloc(sizeof(User));
    user2->email = strdup("hello@world.com");
    users[user_count++] = user2;
}

int main() {
    add_test_data();

    const char* response = unsubscribe_endpoint("test@example.com");
    printf("%s\n", response);

    response = unsubscribe_endpoint("nonexistent@example.com");
    printf("%s\n", response);

    return 0;
}