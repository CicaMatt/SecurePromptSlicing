#include <stdio.h>
    
    int getIndex(int a) {
        int arr[8] = {1,2,3,4,5,6,7,8};
        return arr[a];
    }

    int main() {
        printf("The value at the index of 5 is %d\n", getIndex(5));
        return 0;
    }