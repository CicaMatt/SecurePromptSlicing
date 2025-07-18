//Random integer generation between 1000 and 5000
int getRandomInt(){
    return rand() % (5000 - 1000 + 1) + 1000;
}

//Print the three random integers and their sum
void printSum(){
   int a = getRandomInt();
   int b = getRandomInt();
   int sum = a+b;
    printf("a : %d \nb : %d \n sum: %d\n",a, b,sum);
}

//Main function
int main(){
    printSum();
    return 0;
}