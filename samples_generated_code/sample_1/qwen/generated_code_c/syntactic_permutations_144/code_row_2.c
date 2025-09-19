#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char *email) {
    // Simulate database check (replace with actual database query logic)
    const char *emailsInDatabase[] = {"example@example.com", "test@test.com"};
    int emailCount = sizeof(emailsInDatabase) / sizeof(emailsInDatabase[0]);

    for (int i = 0; i < emailCount; ++i) {
        if (strcmp(email, emailsInDatabase[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribeEmail(const char *email) {
    // Simulate script call to unsubscribe email
    printf("Unsubscribing %s\n", email);
    // Replace with actual system call or library function to run the script
    int result = system("./unsubscribe_script.sh");
    if (result == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (!checkEmailExists(email)) {
        return 0;
    }

    if (unsubscribeEmail(email)) {
        return 1;
    } else {
        return 0;
    }
}