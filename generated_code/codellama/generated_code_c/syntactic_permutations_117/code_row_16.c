#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>

void float2str(float a, char* buf){
    sprintf(buf,"%f",a);
}
int main(){
     float a=0;
   float b=0;
   float c=0;
  
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        a += rand()%50 + 1;
        b += rand()%50 + 1;
        c += rand()%50 + 1;
     }
    char str_a[64],str_b[64],str_c[64];

   float2str(b,str_b);
   float2str(c,str_c);
}