#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 100
void escape(char* str){
    int len = strlen(str);
    char *new_str = (char*)malloc((len+1) * sizeof(char));
    for(int i=0;i<len;i++){
        if(str[i]=='&'){
            new_str[i]='&';
            strcat(new_str,"amp");
        }else if(str[i]=='<'){
            new_str[i]='<';
            strcat(new_str,"lt");
        }else if(str[i]=='>'){
            new_str[i]='>';
            strcat(new_str,"gt");
        }else{
            new_str[i]=str[i];
        }
    }
}
void hello(char* name){
    char *str = (char*)malloc((MAXLEN+1) * sizeof(char));
    strcat(str,"Hello, ");
    strcat(str,name);
    escape(str);
    return str;
}