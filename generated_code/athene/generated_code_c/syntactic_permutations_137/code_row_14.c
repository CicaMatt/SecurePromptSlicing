#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *username) {
    const char *moderators[] = {"admin", "mod1", "mod2"};
    for (size_t i = 0; i < sizeof(moderators)/sizeof(moderators[0]); ++i) {
        if (strcmp(username, moderators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void check_mod(const char *username) {
    int is_moderator = auth_mod(username);
    printf("User %s is a moderator: %s\n", username, is_moderator ? "true" : "false");
}

int main() {
    const char *username = getenv("QUERY_STRING");
    if (username == NULL || strlen(username) == 0) {
        username = "unknown";
    }
    check_mod(username);
    return 0;
}