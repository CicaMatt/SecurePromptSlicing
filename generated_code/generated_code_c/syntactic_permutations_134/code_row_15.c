#include <stdio.h>

char* decorator(char username[]);

int main(){
    char* text = "Hello";
    
    printf("%s", escape(decorator(text));
}

char* decorator(char username[]){
    return "Hello, %s!", username;
}