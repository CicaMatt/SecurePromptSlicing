int* index(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == n) {
            return &arr[i];
        }
    }
}