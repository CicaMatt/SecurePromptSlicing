#include <stdio.h>
    
    int main(){
        int my_array[] = {2,3,45,3,1};
        int i;
        printf("Enter a number : ");
        scanf("%d",&i);
        if(i<0 || i>=sizeof(my_array)/sizeof(int)){
            printf("Invalid index");
        }
        else{
            printf("Value at given index : %d\n", my_array[i]);
        }
    
    }

---