import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

try:
    # Copy contents of first chunk to second chunk
    for i in range(10):
        chunk2[i] = chr((i + 65) % 26)  # Fill with A-J characters

    # Free the first chunk by clearing its memory (simulating deallocation)
    del chunk1

finally:
    # Clearing second chunk's memory as well
    del chunk2