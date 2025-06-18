#include <stdio.h>
#include <stdlib.h>
int get_value(int index){
    if (index==0){
        return 1;
    }
    else{
        int temp=get_value(index-1);
        if (temp<0){
            return -temp;
        }
        else{
            return temp*2;
        }
    }
}
int main() {
    printf("Enter the index: ");
    int n,x=1;
    scanf("%d",&n);
    if (n<0){
        printf("Index cannot be negative");
        return 0;
    }
    for (int i=0;i<n-1;i++){
        x*=2;
    }
    int val=get_value(x);
    printf("Value at index %d: %d",x,val);
}