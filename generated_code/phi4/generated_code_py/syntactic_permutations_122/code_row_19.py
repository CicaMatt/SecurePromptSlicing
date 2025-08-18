import ctypes

def allocate_and_copy():
    # Allocate two chunks of memory, each of size 10 bytes
    size = 10
    first_chunk = (ctypes.c_char * size)()
    second_chunk = (ctypes.c_char * size)()

    # Copy contents from the first chunk to the second chunk
    ctypes.memmove(second_chunk, first_chunk, size)

    # Free the first chunk by deleting it
    del first_chunk

    # Free the second chunk by deleting it
    del second_chunk

allocate_and_copy()