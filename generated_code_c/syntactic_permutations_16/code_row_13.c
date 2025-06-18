//array declaration
int myArray[10] = {34,2,67,5,98,3,43,65,4};

//function to get user input and print value at index
void getInput(int *userInput){
    scanf("%d",userInput);
}

int main() {

  //declare variable for user input
  int userInput;

  //call function to get user input
  getInput(&userInput);

  //print value at index
  printf("Value at index %d is: %d\n", userInput, myArray[userInput]);

}