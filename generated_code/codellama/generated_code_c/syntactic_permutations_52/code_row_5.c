#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    
    void do_login(char *username, char *password) {
        if (strcmp(username, "admin") != 0 || strcmp(password, "secret") != 0) {
            printf("Incorrect username or password.\n");
            return;
        }
    
        int fd = open("/dev/null", O_WRONLY);
        if (fd == -1) {
            perror("Failed to open /dev/null\n");
            exit(EXIT_FAILURE);
        }
    
        char *username_sess = malloc(strlen(username));
        strcpy(username_sess, username);
        char *password_sess = malloc(strlen(password));
        strcpy(password_sess, password);
    
        write(fd, username_sess, strlen(username_sess));
        write(fd, password_sess, strlen(password_sess));
    
        close(fd);
    
        printf("Successfully logged in.\n");
    }
    
    int main() {
        char username[10];
        char password[10];
    
        do_login(username, password);
    
        return 0;
    }