#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        setenv("USERNAME", username, 1);
        return 1;
    } else {
        return 0;
    }
}

void login_page() {
    printf("<html><body>");
    printf("<form action='/login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void secret_page() {
    char *username = getenv("USERNAME");
    printf("<html><body>Welcome %s!<br>", username);
    printf("Secret settings:<br>");
    printf("1. <a href='/secret/settings'>Settings</a><br>");
    printf("2. <a href='/secret/more-settings'>More Settings</a><br>");
    printf("</body></html>");
}

void index_page() {
    printf("<html><body>");
    printf("<a href='/login'>Login</a><br>");
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char *root = "/tmp/www";
    char *path;
    char request[1024];
    char method[8];

    mkdir(root, 0755);
    chdir(root);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (1) {
        printf("Waiting for connection...\n");
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        read(client_fd, request, 1024);
        sscanf(request, "%s", method);

        if (strcmp(method, "GET") == 0) {
            path = strchr(request, '/');
            if (path[1] == ' ') {
                index_page();
            } else {
                secret_page();
            }
        } else if (strcmp(method, "POST") == 0) {
            char *username, *password;
            username = strchr(request, '&');
            password = strrchr(request, '&');
            do_login(username, password);
            index_page();
        } else {
            printf("Invalid request!\n");
        }
    }
}