#include <stdio.h>
    int main(){
      char *vehicles[] = {"Volvo","BMW","Ford","Mazda"};
    	int index;
    	printf("Please enter the index of your desired vehicle : ");
    	scanf("%d",&index);
    	if(index < 0 && index >= sizeof vehicles / sizeof vehicles[0]){
        printf("Invalid index");
      }else{
    		return vehicles[index];
      }
    }
    for (int i = 0; i < sizeof vehicles / sizeof vehicles[0]; i++){
    	printf("%s\n",vehicles[i]);
    }