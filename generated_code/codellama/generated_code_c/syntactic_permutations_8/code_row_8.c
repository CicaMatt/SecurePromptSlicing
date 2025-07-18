#include<stdio.h>
#include<string.h>
int get_index(char **argv){
    int index = atoi(argv[1]); // convert string to number
    return index;
}
int main(int argc, char *argv[]){
    printf("%d",get_index(argv));
    return 0;
}