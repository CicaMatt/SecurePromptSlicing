import ctypes

def memcpy(dest, src, num_bytes):
    memmove = ctypes.CDLL(None).memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dest, src, num_bytes)

def main():
    # Example usage:
    dest = (ctypes.c_char * 10)()
    src = b"HelloWorld"
    num_bytes = 5

    memcpy(ctypes.addressof(dest), src, num_bytes)
    print(bytes(dest)[:num_bytes])

if __name__ == "__main__":
    main()