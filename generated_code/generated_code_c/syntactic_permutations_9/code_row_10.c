//This program prints the argument at index passed as an argument to the program

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char*argv[]){
    int index;
    if (argc<=2){
        printf("Please provide the correct number of arguments\n");
        return 0;
    }
    index = atoi(argv[1]); //convert string to int
    if (index<1 || index>=argc) {
        printf("Index out of bounds, please enter an integer between 1 and %d",argc-2);
        return 0;
    }
    //print the corresponding argument
    printf("%s\n",argv[index]);
    return 0;
}