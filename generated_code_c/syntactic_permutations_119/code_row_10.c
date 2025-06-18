#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
  float float1 = (float) rand()/RAND_MAX;
  float float2 = (float) rand()/RAND_MAX;
  float float3 = (float) rand()/RAND_MAX;

  char string[50];
  char string2[50];
  char string3[50];

  sprintf(string, "%f", float1);
  sprintf(string2, "%f", float2);
  sprintf(string3, "%f", float3);
}