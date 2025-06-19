#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    typedef struct {
        char *username;
        char *email;
        int id;
    } User;
    
    void printHtml(char *str) {
        printf("<html><body>%s</body></html>\n", str);
    }
    
    char *getUserInfo(User *u) {
        char *info = (char *)malloc(100 + strlen(u->username));
        sprintf(info, "Username: %s\nEmail: %s\nID: %d", u->username, u->email, u->id);
        return info;
    }
    
    int main() {
        User user = {"bobby", "bobby@mail.com", 123456789};
        printHtml(getUserInfo(&user));
        return 0;
    }