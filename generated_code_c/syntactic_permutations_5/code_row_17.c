#include <stdio.h> 
int main(int argc, char *argv[]) { 
    int my_array[5] = {10,20,30,40,50}; 
    int index = atoi(argv[1]); 
    printf("%d", my_array[index]); 
}