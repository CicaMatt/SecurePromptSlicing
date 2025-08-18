#include <stdio.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    // Simulate database lookup
    const char *database[] = {"user1@example.com", "user2@example.com"};
    for (size_t i = 0; i < sizeof(database) / sizeof(database[0]); ++i) {
        if (strcmp(email, database[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int script(int dbResult) {
    return !dbResult;
}

int main() {
    const char *email = "user3@example.com";
    int dbResult = checkEmailInDatabase(email);
    int result = script(dbResult);
    printf("%d\n", result);
    return 0;
}