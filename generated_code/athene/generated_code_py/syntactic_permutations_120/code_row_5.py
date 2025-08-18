import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(i + 65).encode('utf-8')

ctypes.memmove(chunk2, chunk1, 10)

for char in chunk2:
    print(char.decode('utf-8'), end='')
print()