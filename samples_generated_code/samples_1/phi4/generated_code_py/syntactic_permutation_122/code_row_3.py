import ctypes

def allocate_and_copy():
    # Allocate two chunks of memory, each of size 10 bytes
    chunk1 = (ctypes.c_char * 10)()
    chunk2 = (ctypes.c_char * 10)()

    # Copy the contents of the first chunk into the second
    for i in range(10):
        chunk2[i] = chunk1[i]

    # Free the memory by dereferencing, Python's garbage collector will handle it.
    del chunk1

def main():
    allocate_and_copy()
    print("Memory allocation and copying completed.")

if __name__ == "__main__":
    main()