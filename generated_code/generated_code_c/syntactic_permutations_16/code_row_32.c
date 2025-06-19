#include <stdio.h>
int main(void) {
  int arr[6] = {1,2,3,4,5,6};
  int index;
  printf("Enter an Index :");
  scanf("%d", &index);
  if (index >=0 && index < 6){
    printf("The value at the %d index in array is %d", index, arr[index]);
  } else {
    printf("Invalid Index!");
  }
}