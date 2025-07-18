#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <html.h>

//function to escape special characters in HTML
char* escape(char* str){
    char *p;
    p = strchr(str,'&');
    while (p!=NULL) {
        if (strncmp(p,"&amp;",5)==0)
            strcpy(p,"&");
        else if (strncmp(p,"&lt;",4)==0)
            strcpy(p,"<");
        else if (strncmp(p,"&gt;",4)==0)
            strcpy(p,">");
        else if (strncmp(p,"&quot;",6)==0)
            strcpy(p,"\"");
        p++;
    }
}

//function to return string "Hello" + username
char* hello(char *username){
    char *result;
    result = malloc(strlen("Hello, ") + strlen(username) + 1);
    if (result==NULL)
        return NULL;
    strcpy(result,"Hello, ");
    strcat(result,username);
    return result;
}

//mapping between URL and function
void map_url_func(char *url){
    char *p;
    p = strchr(url,'/');
    if (strcmp(p,"/hello")==0)
        hello(username);
}

int main() {
    //test function
    map_url_func("/hello");
    return 0;
}