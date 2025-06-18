#include<stdio.h>
int main() {
  char *vehicles[4] = {"car", "bus", "train" , "bike"};
  int index;
  printf("Enter the index of a vehicle to be printed out\n");
  scanf("%d", &index);
  for(int i=0;i<4;i++){
    if (i==index){
      printf("%s", vehicles[index]);}
  }
  

  return 0;
}