import ctypes

def memcpy(dest, src, num_bytes):
    mem_move = ctypes.CDLL(None).memmove
    mem_move.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    mem_move.restype = ctypes.c_void_p
    return mem_move(dest, src, num_bytes)

# Example usage:
dest_ptr = (ctypes.c_char * 10)()
src_ptr = (ctypes.c_char * 10)()

for i in range(10):
    src_ptr[i] = chr(i + ord('0'))

memcpy(ctypes.addressof(dest_ptr), ctypes.addressof(src_ptr), 10)

for i in range(10):
    print(dest_ptr[i])