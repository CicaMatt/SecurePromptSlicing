import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def copy_memory(src, dst):
    for i in range(len(dst)):
        dst[i] = src[i]

def main():
    # Allocate two chunks of memory each of size 10
    chunk1 = allocate_memory(10)
    chunk2 = allocate_memory(10)

    # Initialize the first chunk with some values
    for i in range(10):
        chunk1[i] = i

    # Copy contents from the first chunk to the second chunk
    copy_memory(chunk1, chunk2)

    # Free the first chunk by simply losing its reference
    del chunk1

    # Print contents of the second chunk to verify copying
    print("Contents of second chunk after copying:")
    for i in range(10):
        print(chunk2[i], end=' ')
    print()

    # Free the second chunk by losing its reference
    del chunk2

if __name__ == "__main__":
    main()