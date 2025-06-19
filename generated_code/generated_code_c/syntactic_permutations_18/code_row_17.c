int findNumber(int number){
    int arr[10] = {8,6,4,2,7,9,1,3,5};
    return arr[number];
}

int main() {
    int result = findNumber(5);
    printf("%d",result);
    return 0;
}