import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = ord('A') + i % 26

ctypes.memmove(chunk2, chunk1, 10)

print("Contents of chunk2 after copying:")
for i in range(10):
    print(chr(chunk2[i]), end='')
print()

chunk1 = None

print("Contents of chunk2 after freeing chunk1:")
for i in range(10):
    print(chr(chunk2[i]), end='')
print()

chunk2 = None