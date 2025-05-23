import ctypes

def memcpy(dest, src, num_bytes):
    memmove = ctypes.CDLL('libc.so.6').memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

class MemoryBlock:
    def __init__(self, size):
        self.size = size
        self.data = bytearray(size)

    def __getitem__(self, index):
        if isinstance(index, int):
            return self.data[index]
        else:
            start, stop, step = index.start, index.stop, index.step
            return self.data[start:stop:step]

    def __setitem__(self, index, value):
        if isinstance(index, int):
            self.data[index] = value
        else:
            start, stop, step = index.start, index.stop, index.step
            for i in range(start, stop, step):
                self.data[i] = value

dest_block = MemoryBlock(10)
src_block = MemoryBlock(5)

for i in range(5):
    src_block[i] = i + 1

memcpy(dest_block.data, src_block.data, 5)

for byte in dest_block[:5]:
    print(byte)