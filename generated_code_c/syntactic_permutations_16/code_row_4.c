// This function takes an integer as input and returns the value at the index of the integer in the array. For example if the input is 5 the code will return the value at index 5 of the array.If the input is 0 the code will return the value at index 0 of the array.
int findValueAt(int arr[], int n, int index) {
    // Check for error cases: if the index is less than zero or greater than the size of the array
    if (index < 0 || index >= n)
        return -1; // If an error occurs return -1
    else
        return arr[index]; // Otherwise, return the value at the index
}