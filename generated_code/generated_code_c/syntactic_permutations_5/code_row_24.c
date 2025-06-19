int main(void) {
    int n = 5;
    int arr[n];

    for (int i = 0; i < n; i++) {
        printf("Enter %d number: ", i + 1);
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("Element at position %d is: %d\n", i, arr[i]);
    }

    return 0;
}