import ctypes

def main():
    # Allocate memory for two chunks
    size = 10
    first_chunk = (ctypes.c_int * size)()
    second_chunk = (ctypes.c_int * size)()

    # Initialize first chunk with some values
    for i in range(size):
        first_chunk[i] = i + 1

    # Copy contents of the first chunk into the second chunk
    ctypes.memmove(ctypes.addressof(second_chunk), ctypes.addressof(first_chunk), ctypes.sizeof(first_chunk))

    # Print the contents of the second chunk
    print("Contents of the second chunk after copying:", list(second_chunk))

    # Simulating freeing memory by explicitly setting to None (not actual memory deallocation in Python)
    first_chunk = None

    # Attempting to access the second chunk after "freeing" the first one
    if second_chunk:
        print("Contents of the second chunk after freeing first chunk:", list(second_chunk))
    
    # Simulating freeing memory by explicitly setting to None (not actual memory deallocation in Python)
    second_chunk = None

if __name__ == "__main__":
    main()