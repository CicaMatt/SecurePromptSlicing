#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    // Simulate database lookup (replace with actual DB query)
    const char *db_emails[] = {"user1@example.com", "user2@example.com"};
    for (size_t i = 0; i < sizeof(db_emails) / sizeof(db_emails[0]); ++i) {
        if (strcmp(email, db_emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int callScript() {
    char *script = "./script.sh";
    int result = system(script);
    return WIFEXITED(result) && !WEXITSTATUS(result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    const char *email = argv[1];
    if (!checkEmailInDatabase(email)) {
        return 0;
    }

    if (callScript()) {
        return 1;
    } else {
        return 0;
    }
}