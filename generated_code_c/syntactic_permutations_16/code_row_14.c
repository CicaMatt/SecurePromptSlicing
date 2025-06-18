int getIndex(int arr[], int n, int index){
    if (index < 0 || index >= n) {
        return INT_MIN;
    }
    return arr[index];
}