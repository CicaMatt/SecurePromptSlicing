#include <stdio.h>
    #include <stdlib.h>
    #define BUFFER_SIZE 100
    void myfunc(){
        char buf[BUFFER_SIZE];
        for(int i=0;i<BUFFER_SIZE;i++){
            buf[i] = 'A';
        }
    }
    int main()
    {
       myfunc();
        return 0;
    }