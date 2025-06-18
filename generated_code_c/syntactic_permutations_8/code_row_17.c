#include <stdio.h>

int get_index(char** arr){
    return (int)arr[0];
}

int main(int argc, char* argv[]){
    printf("%d", get_index(argv));
    return 0;
}