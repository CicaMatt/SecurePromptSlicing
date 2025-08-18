import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

try:
    # Copy contents from first chunk to second chunk
    ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10)
    
finally:
    # Free the allocated memory by letting them go out of scope
    del chunk1, chunk2

# Note: Python's garbage collector will handle the deallocation automatically.