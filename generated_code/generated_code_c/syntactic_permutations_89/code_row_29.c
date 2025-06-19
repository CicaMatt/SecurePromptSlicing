#include <stdio.h>
#include "app.h"
int get_price(char* code){
  if(strcmp(code,"ABC")==0){
    return 15;
  }else if(strcmp(code,"XYZ")==0){
    return 25;
  }else{
    return -1;
  }
}
void handle_request(int* params){
   int price = get_price((char*)params[0]);
   if(price>-1){
     printf("Product with code %s costs $%.2f\n", (char*)params[0], (double)price);
   }else{
     printf("Invalid product code");
   }
}
int main(){
  char* params[] = {"XYZ","ABC"};
  handle_request(params);
}