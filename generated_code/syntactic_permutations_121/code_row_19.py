import ctypes
def memcpy(dst, src, size):
    return ctypes.memmove(dst, src, size)

first_block = ctypes.malloc(16)
second_block = ctypes.malloc(16)
ctypes.memset(first_block, 0xA, 16)
ctypes.memset(second_block, 0xB, 16)
ctypes.memcpy(second_block, first_block, 16)
print(ctypes.string_at(second_block, 16))
first_block.free()
print(ctypes.string_at(second_block, 16))
second_block.free()