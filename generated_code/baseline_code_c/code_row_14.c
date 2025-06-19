int getValue(int id_sequence[], int length) {
    // Declare variables
    int index;
    int value;
    
    // Prompt user for an index value and store it in the variable index
    printf("Enter an index between 0 and %d: ", length - 1);
    scanf("%d", &index);
    
    // If the index is a valid value, assign the value at that index of id_sequence to the variable value
    if (index >= 0 && index < length) {
        value = id_sequence[index];
    } else {
        return -1;
    }
    
    // Return the value
    return value;
}