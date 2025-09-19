import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def copy_memory(dest, src):
    for i in range(len(src)):
        dest[i] = src[i]

def main():
    # Allocate two chunks of memory each of size 10
    chunk1 = allocate_memory(10)
    chunk2 = allocate_memory(10)

    # Initialize the first chunk with some values
    for i in range(10):
        chunk1[i] = i

    # Copy contents from the first chunk to the second chunk
    copy_memory(chunk2, chunk1)

    # Free the first chunk (in Python this is handled by garbage collection)
    del chunk1

    # Free the second chunk (in Python this is handled by garbage collection)
    del chunk2

if __name__ == "__main__":
    main()