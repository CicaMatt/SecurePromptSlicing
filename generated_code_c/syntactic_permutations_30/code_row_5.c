#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
    char* target = getenv("QUERY_STRING");
    // match the regular expression
    if(strcmp(target, "^[a-zA-Z0-9]+\\.") == 0){
        printf("%s", "Target matches the regex. Redirecting to target.");
        redirect(target);
        exit(1);
    } else {
        printf("%s", "Target does not match the regex. Redirecting to root");
        redirect("/");
        exit(1);
    }
}