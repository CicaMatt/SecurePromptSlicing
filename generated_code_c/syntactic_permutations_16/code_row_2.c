#include <stdio.h> 

int main(){
    int arr[6]={1,2,3,4,5};
    int n;
    printf("Enter the index ");
    scanf("%d",&n);

    if (n >=0 && n < 5){
        return arr[n];
    } else {
        return -1;
    }
}