#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
void hello(char *username){
    char buf[MAX];
    strcpy(buf, "Hello, ");
    strcat(buf, username);
    puts(html_escape(buf));
}
char* html_escape(char* s){
    int i = 0;
    while(s[i]){
        if(s[i] == '&'){
            strcpy(&s[i], "&amp;");
            i += 4;
        }
        else if(s[i] == '<'){
            strcpy(&s[i], "&lt;");
            i += 3;
        }
        else if(s[i] == '>'){
            strcpy(&s[i], "&gt;");
            i += 3;
        }
        else if(s[i] == '"'){
            strcpy(&s[i], "&quot;");
            i += 5;
        }
        else{
            i++;
        }
    }
    return s;
}
int main(){
    char *username = getenv("REMOTE_USERNAME");
    hello(username);
    return 0;
}