#include <stdio.h>  //for IO
#define SIZE 5       //to set size of the array
int getIndex(int id_sequence[SIZE]); //Function declaration to avoid error before definition
int main(){
    int id_sequence[SIZE]={1,2,3,4,5};  //array initialization
    printf("Enter index:");            //prompt for user input
    scanf("%d",&id_sequence);          //scanf to store value at the entered index
    return getIndex(id_sequence[SIZE]);//returning the value at the index in id_sequence 
}
int getIndex(int id_sequence[SIZE]){   //Function definition
    int index;                         //declaration of variable 'index' to store user input
    printf("Enter index:");            //prompt for user input
    scanf("%d",&index);                //scanf to store value at the entered index
    return id_sequence[index];         //returning the value at the index in id_sequence 
}