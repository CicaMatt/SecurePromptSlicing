#include <stdio.h>
#include <stdbool.h>

// Simulate user session data
typedef struct {
    bool isLoggedIn;
    bool isAdmin;
} UserSession;

void redirectUser(const UserSession* session) {
    if (!session->isLoggedIn) {
        printf("Redirecting to login page...\n");
    } else if (session->isAdmin) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }
}

int main() {
    UserSession session1 = {false, false}; // Not logged in
    UserSession session2 = {true, false};  // Logged in as regular user
    UserSession session3 = {true, true};   // Logged in as admin

    redirectUser(&session1);
    redirectUser(&session2);
    redirectUser(&session3);

    return 0;
}