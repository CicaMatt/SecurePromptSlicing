int getIndexValue(int arr[], int n, int index) {
    for (int i = 0; i < n; i++) {
        if (i == index) {
            return arr[index];
        }
    }
}