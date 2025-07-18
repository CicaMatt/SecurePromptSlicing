#include <stdio.h>
    //function to get index number from user
    int getIndexNumber();
    //function to generate array
    void arrayGenerator(int array[],int size);
    //main function 
    int main() {
        //declare a variable of type integer 
        int index;
        //array of integers
        int array[10] ={};
        //call the function getIndexNumber to get the index number from user 
        index=getIndexNumber();
        //pass the array and its size as argument to the array generator function
        arrayGenerator(array,sizeof(array));
        //print out the value at the index of the array
        printf("The value at the index %d is %d\n",index,array[index]);
    }
     //function to get index number from user
    int getIndexNumber(){
       //declare a variable of type integer 
        int index;
        //print out message for user to enter index number
        printf("Enter the index number: ");
        //get value from user and store it in the variable index
        scanf("%d", &index);
        //return the value entered by the user as index number
        return index;
    }
     //function to generate array
    void arrayGenerator(int array[],int size){
       //loop through each element of the array and initialize it with a random integer  between 100 and 200
       for(int i=0;i<size;i++){
           array[i]=rand() % 100+100;
        }
    }