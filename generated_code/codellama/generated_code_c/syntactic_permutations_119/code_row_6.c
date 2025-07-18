#include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 
 int main(void){
 float r1, r2,r3;
 char str1[20],str2[20],str3[20];
  srand((unsigned) time(&t));
  r1 = (float)(rand() % 10);
  r2= (float)(rand() % 10);
  r3=(float)(rand() % 10);
  sprintf(str1,"%f",r1);
  sprintf(str2,"%f",r2);
  sprintf(str3,"%f",r3);
  printf("%s, %s, %s\n",str1, str2,str3); 
 }