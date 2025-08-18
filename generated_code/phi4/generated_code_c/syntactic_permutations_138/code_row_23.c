#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

void is_moderator(char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT role FROM users WHERE username='%s'", username);

    FILE *pipe = popen("mysql -h %s -u %s -p%s %s -e \"%s\"", DB_HOST, DB_USER, DB_PASS, DB_NAME, query);
    
    if (pipe == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    char result[256];
    if (fgets(result, sizeof(result), pipe) != NULL) {
        printf("Role: %s", result);
    } else {
        printf("User not found or error occurred.\n");
    }
    
    pclose(pipe);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    is_moderator(argv[1]);

#ifdef _WIN32
    system("pause");
#else
    sleep(1);
#endif

    return 0;
}