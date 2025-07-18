import ctypes
def copy_chunks(chunk1, chunk2):
    memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), len(chunk1))
    print("Second chunk contains", chunk2)