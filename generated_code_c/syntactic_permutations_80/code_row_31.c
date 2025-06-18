#include<stdio.h>
int main(){
     char buffer[1024];
   int num;
    scanf("%1023[^\n]%*c",buffer);
    printf("%s\n",buffer);
}