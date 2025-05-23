import ctypes

def memcpy(dest, src, count):
    memmove = ctypes.CDLL('libc.so.6').memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dest, src, count)

def main():
    # Example usage:
    buffer1 = bytearray(b'Hello, world!')
    buffer2 = bytearray(b'\x00' * 20)
    memcpy(ctypes.addressof(ctypes.c_char.from_buffer(buffer2)), 
           ctypes.addressof(ctypes.c_char.from_buffer(buffer1)), 
           len(buffer1))
    print(buffer2)

if __name__ == "__main__":
    main()