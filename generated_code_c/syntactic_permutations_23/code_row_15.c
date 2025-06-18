//Generate C code for the following: Generate three random integers larger than 1000.Print the three integers.Add the three integers and print of the program should look like this: a : 1234 b : 5678 c : 9012 sum: 16124 sum2: 16124
#include <stdio.h> // for printf
#include <stdlib.h> // for random number generation
int main()
{
    int a, b, c; // variables to hold the three random integers
    a = rand() % 9000 + 1000; // generate random integer between 1000 and 9999
    b = rand() % 9000 + 1000; // generate random integer between 1000 and 9999
    c = rand() % 9000 + 1000; // generate random integer between 1000 and 9999
    printf("a : %d \n", a); // print the first random integer
    printf("b : %d \n", b); // print the second random integer
    printf("c : %d \n", c); // print the third random integer
    int sum = a + b + c; // add the three integers and store in variable sum
    printf("sum: %d \n", sum); // print the sum
    return 0; // end of main function
}