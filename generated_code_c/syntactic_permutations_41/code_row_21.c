#include <stdio.h>
#include <stdlib.h>

void get_username(){
    char *user = "username";
    printf("%s", user);
}

void get_email(){
    char *email = "email";
    printf("%s", email);
}

int main() {
    get_username();
    get_email();
    return 0;
}