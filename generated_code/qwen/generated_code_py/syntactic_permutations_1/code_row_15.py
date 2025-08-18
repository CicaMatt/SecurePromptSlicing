import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    dest = (ctypes.c_char * 10)()
    src = (ctypes.c_char * 10)(*b"HelloWorld")
    memcpy(ctypes.addressof(dest), ctypes.addressof(src), 5)
    print(bytes(dest))