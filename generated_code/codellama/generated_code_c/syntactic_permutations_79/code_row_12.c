#include<stdio.h>
#include <stdlib.h>
void read_data(){
    char* buf = malloc(1024);
    scanf("%1023s",buf); 
}
void read_data1(){
    char* buf1 = malloc(1024);
    scanf("%1023s",buf1);
}
int main() {
    read_data();
    read_data1();
    return 0;
}