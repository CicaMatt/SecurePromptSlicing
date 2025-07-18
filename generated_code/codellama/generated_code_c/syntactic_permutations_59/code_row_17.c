#include<stdio.h>

    #include<stdlib.h>



    void overwriteBuffer(char* buffer, int bufferSize){

        for(int i = 0; i < bufferSize; i++){

            buffer[i] = 'A';

        }

    }
