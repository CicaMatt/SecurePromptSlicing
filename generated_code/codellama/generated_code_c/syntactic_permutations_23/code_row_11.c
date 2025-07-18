int main(){
    int a,b,c;
    srand(time(NULL));
    a=rand()%100+1000;
    b=rand()%100+1000;
    c=rand()%100+1000;
    printf("a : %d\nb : %d\nc : %d\nsum: %d\n",a,b,c,a+b);
}