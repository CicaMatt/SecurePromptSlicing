#include <stdio.h> //For printf function

int main(){
    int i;
    int buffer_size = 1024;
    char buffer[buffer_size];

    for(i=0; i<buffer_size; i++){
        buffer[i] = 'A';
    }
}