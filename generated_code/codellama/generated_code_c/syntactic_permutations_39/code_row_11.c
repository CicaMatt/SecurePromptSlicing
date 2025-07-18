#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

struct user {
    char *username;
    char *password;
};

struct session {
    int id;
    struct user user;
};

void redirect_to_session(int session_id) {
    printf("HTTP/1.1 302 Found\n");
    printf("Location: /sessions/%d", session_id);
}

void login(struct user *user) {
    if (strcmp(user->username, "admin") == 0 && strcmp(user->password, "password123") == 0) {
        struct session session;
        session.id = rand();
        session.user = *user;
        redirect_to_session(session.id);
    } else {
        printf("HTTP/1.1 401 Unauthorized\n");
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<!DOCTYPE html>\n");
        printf("<html>\n");
        printf("<head>\n");
        printf("<title>Unauthorized</title>\n");
        printf("</head>\n");
        printf("<body>\n");
        printf("<h1>Unauthorized</h1>\n");
        printf("<p>Username or password is incorrect.</p>\n");
        printf("</body>\n");
        printf("</html>\n");
    }
}

int main() {
    char *username = getenv("QUERY_STRING");
    char *password = getenv("HTTP_AUTHORIZATION");
    struct user user;
    user.username = username;
    user.password = password;
    login(&user);
    return 0;
}
