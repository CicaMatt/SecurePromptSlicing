import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

try:
    # Initialize the first chunk with some data
    for i in range(10):
        chunk1[i] = b'A' + bytes([i])

    # Copy contents of the first chunk to the second chunk
    ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10)

finally:
    # Free the first chunk (in Python, this is implicit with garbage collection)
    del chunk1

    # Explicitly free the second chunk using deletion
    del chunk2