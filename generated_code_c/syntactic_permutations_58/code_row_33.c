// User data structure
struct User {
    char *email;
    char *password;
};
// Function to update user email
void updateEmail(struct User user, const char *newEmail) {
    if (user.email != NULL && user.password != NULL) {
        free(user.email);
        free(user.password);
    }
    // Update user email and password
    user.email = strdup(newEmail);
    user.password = strdup("newPassword");
}
// Function to login with old email and password
int loginWithOldEmailAndPassword(const char *oldEmail, const char *password) {
    if (strcmp(oldEmail, "user@example.com") == 0 && strcmp(password, "password") == 0) {
        // Login success
        return 1;
    } else {
        // Login failed
        return 0;
    }
}
// Main function
int main() {
    struct User user = {"user@example.com", "password"};
    char newEmail[64];
    printf("Enter new email: ");
    scanf("%63s", newEmail);
    if (loginWithOldEmailAndPassword(user.email, user.password)) {
        updateEmail(user, newEmail);
        printf("Email updated successfully\n");
    } else {
        printf("Invalid old email or password\n");
    }
    return 0;
}