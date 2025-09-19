import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def main():
    # Allocate two chunks of memory, each of size 10
    chunk1 = allocate_memory(10)
    chunk2 = allocate_memory(10)

    # Fill the first chunk with some values for demonstration purposes
    for i in range(10):
        chunk1[i] = i

    # Copy contents of the first chunk into the second chunk
    ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10 * ctypes.sizeof(ctypes.c_int))

    # Free the first chunk by simply not using it anymore in Python (garbage collection will handle this)
    del chunk1

    # No need to explicitly free memory for chunk2 as well; let's just simulate a cleanup
    del chunk2

if __name__ == "__main__":
    main()