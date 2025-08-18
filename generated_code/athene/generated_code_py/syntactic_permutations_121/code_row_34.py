import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, len(chunk1))

print(''.join(map(chr, chunk2[:len(chunk1)])))

chunk1 = None

print(''.join(map(chr, chunk2[:len(chunk2)])))

chunk2 = None