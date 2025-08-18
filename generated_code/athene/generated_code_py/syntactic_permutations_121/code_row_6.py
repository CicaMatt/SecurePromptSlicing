import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(ord('a') + i).encode()

ctypes.memmove(chunk2, chunk1, len(chunk1))

print("Contents of chunk2 after copy:", bytes(chunk2[:]).decode())

chunk1 = None

print("Contents of chunk2 after freeing chunk1:", bytes(chunk2[:]).decode())

chunk2 = None