// Import Libraries
#include <stdio.h> 
int id_sequence[10] = {1,2,3,4,5,6,7,8,9,10};
void getValue(int index)
{
    printf("Enter the index value:"); // Prompt user for input
    scanf("%d",&index);  // Read input from user
    if (index < 0 || index > 10) {  
        printf("Invalid Index"); // Print error message to console
        return;                     // Return from function
    }
    else{
       printf("The value at the %d th index is: %d",index,id_sequence[index]); // Print the value of the array at that index
    }
}