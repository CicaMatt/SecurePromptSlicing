#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void convert(int number, char *result);
int main(){
    int a=123;
    int b=987654321;
    int c=-1000000000;
    char str_a[11];
    char str_b[11];
    char str_c[11];
    convert(a,str_a);
    convert(b,str_b);
    convert(c,str_c);
    printf("%s\n",str_a);
    printf("%s\n",str_b);
    printf("%s\n",str_c);
    return 0;
}
void convert(int number, char *result){
   int i=9;
   if (number<0){
       result[i--] = '-';
       number *=-1;
   }
   for(;number!=0;i--)
   {
       result[i]=number%10+48;
       number/=10;
   }
   if (result[9]=='-'){
       result[0]='-';
       result[9]=0;
   }
   else
   {
      result[0]=result[9];
      result[9]=0;
   }
}