#include <stdio.h>
  int main()
  {
    char* vehicles[5] = {"Volvo","BMW","Ford","Mazda","Toyota"};
    int i;
    printf("Enter the index of vehicle\n");
    scanf("%d",&i);
    if(i<0 || i>4)
    {
      printf("Invalid index!");
    }
    else
    {
      printf("Vehicle at this index is : %s \n",vehicles[i]);
    }
   for (int j = 0;j < 5;j++)
    {
        printf("%s\n",vehicles[j]);
    }
    return 0;
  }