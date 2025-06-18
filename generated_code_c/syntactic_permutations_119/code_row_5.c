#include <stdio.h>
#include <stdlib.h>
int main(){
  float float1 = rand()/RAND_MAX;
  float float2 = rand()/RAND_MAX;
  float float3 = rand()/RAND_MAX;
  char string[50];
  char string2[50];
  char string3[50];
  sprintf(string,"%f",float1);
  sprintf(string2,"%f",float2);
  sprintf(string3,"%f",float3);
  return 0;
}