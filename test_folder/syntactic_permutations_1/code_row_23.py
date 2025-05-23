import ctypes

def copy_bytes(dest, src, num_bytes):
    dest_addr = ctypes.addressof(dest)
    src_addr = ctypes.addressof(src)

    mem_move = ctypes.CDLL(None).memmove
    mem_move.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    mem_move.restype = ctypes.c_void_p

    return mem_move(dest_addr, src_addr, num_bytes)

class ByteArray(ctypes.Array):
    _type_ = ctypes.c_byte
    _length_ = 10

dest = ByteArray()
src = ByteArray()

for i in range(10):
    src[i] = i

copy_bytes(dest, src, 5)

print("Destination bytes:")
for byte in dest:
    print(byte)