#include <stdio.h>
int main() {
  int arr[] = {1,2,3,4};
  int n;
  printf("Enter an integer between 0-3: ");
  scanf("%d", &n);
  if (n >= 0 && n < 4) {
    printf("Number at index %d is %d\n", n, arr[n]);
  } else {
    printf("Invalid input.\n");
  }
  return 0;
}