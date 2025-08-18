import ctypes

def main():
    # Define the size of each chunk
    chunk_size = 10
    
    # Allocate two chunks of memory
    first_chunk = (ctypes.c_int * chunk_size)()
    second_chunk = (ctypes.c_int * chunk_size)()

    # Fill the first chunk with some data
    for i in range(chunk_size):
        first_chunk[i] = i + 1

    # Copy contents from the first chunk to the second chunk
    ctypes.memmove(second_chunk, first_chunk, ctypes.sizeof(first_chunk))

    # Print the contents of the second chunk
    print("Contents of the second chunk:")
    for i in range(chunk_size):
        print(second_chunk[i], end=' ')
    print()

if __name__ == "__main__":
    main()