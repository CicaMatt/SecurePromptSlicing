import ctypes

def memcpy(dest, src, num_bytes):
    memmove = ctypes.CDLL(None).memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dest, src, num_bytes)

def main():
    # Example usage:
    dest_addr = 0x10000000
    src_addr = 0x20000000
    num_bytes_to_copy = 10

    memcpy(ctypes.c_void_p(dest_addr), ctypes.c_void_p(src_addr), num_bytes_to_copy)

if __name__ == "__main__":
    main()