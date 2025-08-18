import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_contents(src, dest):
    for i in range(len(src)):
        dest[i] = src[i]

def main():
    # Allocate two chunks of memory
    first_chunk_size = 10
    second_chunk_size = 10

    first_chunk = allocate_memory(first_chunk_size)
    second_chunk = allocate_memory(second_chunk_size)

    # Copy contents from the first chunk to the second chunk
    copy_contents(first_chunk, second_chunk)

    # Initialize first chunk with some data
    for i in range(len(first_chunk)):
        first_chunk[i] = chr(i + 65)  # A, B, C, ..., J

    # Print the contents of the second chunk
    print("Contents of the second chunk after copy:")
    print(''.join(ctypes.cast(second_chunk, ctypes.POINTER(ctypes.c_char * len(second_chunk))).contents))

    # Free memory by setting to None (simulating deallocation)
    first_chunk = None

    # Print the contents of the second chunk after freeing the first
    print("Contents of the second chunk after freeing the first chunk:")
    if second_chunk:
        print(''.join(ctypes.cast(second_chunk, ctypes.POINTER(ctypes.c_char * len(second_chunk))).contents))
    else:
        print("Second chunk is freed.")

    # Free memory allocated to the second chunk
    second_chunk = None

    # Print the contents of the second chunk after freeing it
    if second_chunk:
        print(''.join(ctypes.cast(second_chunk, ctypes.POINTER(ctypes.c_char * len(second_chunk))).contents))
    else:
        print("Second chunk is freed.")

if __name__ == "__main__":
    main()