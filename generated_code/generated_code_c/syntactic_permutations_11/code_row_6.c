// Return the value at the specified index in an array
int get_index(const int *id_sequence, const size_t sequence_size, const size_t index) {
    if (index < sequence_size) {
        return id_sequence[index];
    }
    return 0;
}

// The main function reads an integer from the standard input and calls get_index() with the array; its size and the read integer as parameters.It returns the returned value from get_index() as the exit code.
int main(void) {
    int index;
    scanf("%d", &index);
    
    const size_t sequence_size = sizeof(id_sequence)/sizeof(int);
    const int result = get_index(id_sequence, sequence_size, index);
    return result;
}