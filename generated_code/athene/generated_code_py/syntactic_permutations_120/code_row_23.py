import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(i + ord('A'))

ctypes.memmove(chunk2, chunk1, 10)

print("".join(map(chr, chunk2)))