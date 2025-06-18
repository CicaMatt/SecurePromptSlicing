#include<stdio.h>
int get_id(int x);
void main() {
    int n;
    printf("Enter a value\n");
    scanf("%d",&n);
    int r=get_id(n);
    printf("The id is %d\n",r);
}
int get_id(int x)
{
    int id_sequence[10]={2,43,56,7,89,32,12,45,68};
    return id_sequence[x];
}