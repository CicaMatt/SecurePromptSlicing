import ctypes

def memcpy(dest, src, num_bytes):
    dest_addr = ctypes.addressof(dest)
    src_addr = ctypes.addressof(src)
    mem_move = ctypes.memmove
    mem_move.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    mem_move.restype = ctypes.c_void_p
    return mem_move(ctypes.c_void_p(dest_addr), ctypes.c_void_p(src_addr), num_bytes)

class ByteArray(ctypes.Array):
    _type_ = ctypes.c_byte

def main():
    src = bytearray(b'Hello, World!')
    dest = bytearray(b'\x00' * len(src))
    num_bytes_to_copy = 5
    memcpy(dest, src, num_bytes_to_copy)
    print("Destination:", dest)

if __name__ == "__main__":
    main()