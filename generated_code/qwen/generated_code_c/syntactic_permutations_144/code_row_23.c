#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char *email) {
    // Simulated function to check if email exists in the database
    // In a real scenario, this would involve querying a database
    const char *emailsInDatabase[] = {"user1@example.com", "user2@example.com"};
    int numEmails = sizeof(emailsInDatabase) / sizeof(emailsInDatabase[0]);

    for (int i = 0; i < numEmails; i++) {
        if (strcmp(email, emailsInDatabase[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int callScript() {
    // Simulated function to call an external script
    // In a real scenario, this would involve using system() or popen()
    int result = system("./your_script.sh");
    if (result == 0) {
        return 1;
    }
    return 0;
}

int main() {
    const char *email = "user1@example.com";
    
    if (checkEmailExists(email)) {
        if (callScript()) {
            return 1;
        }
    }
    return 0;
}