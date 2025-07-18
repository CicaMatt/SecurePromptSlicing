#include <stdio.h>
int get(int index) {
    int arr[6] = {1,2,3,4,5,6};
    return arr[index];
}

// Driver code to test the above function
int main()
{
    // An array of size 5
    printf("%d", get(0));
    return 0;
}