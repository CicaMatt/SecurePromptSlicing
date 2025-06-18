int getValueOfArray(int arr[], int n, int index){
    // Check for the validity of the index
    if (index < 0 || index >=n) {
        return -1;
    }
    
    // Return value at the given index.
    return arr[index];
}