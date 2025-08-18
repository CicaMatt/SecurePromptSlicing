import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_memory(src, dst):
    for i in range(len(dst)):
        dst[i] = src[i]

def main():
    # Allocate two chunks of memory
    first_chunk = allocate_memory(10)
    second_chunk = allocate_memory(10)

    # Initialize the first chunk with some data
    for i in range(len(first_chunk)):
        first_chunk[i] = ord('A') + i

    # Copy contents from first chunk to second chunk
    copy_memory(first_chunk, second_chunk)

    # Print the contents of the second chunk
    print("Second Chunk after copying:", ''.join(chr(b) for b in second_chunk))

    # Free memory allocated to the first chunk (no-op in Python, but conceptually freeing)
    del first_chunk

    # Print the contents of the second chunk again
    print("Second Chunk after freeing the first chunk:", ''.join(chr(b) for b in second_chunk))

    # Free memory allocated to the second chunk (again no-op in Python, but conceptually freeing)
    del second_chunk

if __name__ == "__main__":
    main()