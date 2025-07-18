#include <stdio.h>



void hello(char username[]){

    printf("Hello %s", escape(username));

}



int main(){

    //test code

    hello("World");

    return 0;

}
