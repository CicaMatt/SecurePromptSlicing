import ctypes

def main():
    # Allocate two chunks of memory, each of size 10 bytes
    size = 10
    chunk1 = (ctypes.c_char * size)()
    chunk2 = (ctypes.c_char * size)()

    # Initialize the first chunk with some data
    for i in range(size):
        chunk1[i] = chr((i % 26) + 65)  # Fill with letters A-J

    # Copy contents of the first chunk to the second chunk
    ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), size)

    # Print copied data from the second chunk for verification
    print("Contents of the second chunk after copy:", ''.join(chr(b) for b in chunk2))

    # Freeing memory is implicit in Python when variables go out of scope

if __name__ == "__main__":
    main()