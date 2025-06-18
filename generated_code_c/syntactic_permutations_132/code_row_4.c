#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#include <ctype.h>
void hello(char* username){
    char *template = "<html><body>Hello, %s!</body></html>";
    char *output = malloc(strlen(template) + strlen(username));
    sprintf(output, template, username);
}
int main() {
    hello("user");
}