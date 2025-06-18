#include <stdio.h> // imports printf library
#include <stdlib.h>//imports exit() function
int main(int argc,char*argv[]){  //main funtion 
    if(argc != 2){ //checks for number of arguments
        printf("Usage:./programName value\n");//prints error message with usage
        exit(1);//exits program
    }
     int val;// declares an integer variable val
      val = atoi(argv[1]);//stores the value passed as an argument in val
       printf("Value: %d\n",val+1000);//prints the value after adding 1000 to it
         return 0;//returns zero indicating sucessfull execution
}