// function to return the value at a particular index of the array
int get_value_at_index(int arr[], int index) {
    // check for valid index
    if (index >= 0 && index < sizeof(arr) / sizeof(arr[0])) {
        return arr[index];
    } else {
        printf("Invalid index");
        return -1;
    }
}