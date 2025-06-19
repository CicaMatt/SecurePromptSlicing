#include <stdio.h>

    char* get_username(char* url) {
        int i = 0;
        while (url[i] != '/') i++;
        return &url[i + 1];
    }

    void hello(char* username) {
        printf("Hello %s!", username);
    }

    int main() {
        char* url = "/hello/John";
        hello(get_username(url));
        return 0;
    }