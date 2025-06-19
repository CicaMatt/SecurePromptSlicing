int getValue(int arr[], int n, int index) {
    if (index < 0 || index >= n) {
        return -1;
    }
    return arr[index];
}