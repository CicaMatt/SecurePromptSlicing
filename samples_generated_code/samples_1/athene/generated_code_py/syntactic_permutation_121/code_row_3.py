import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

for i in range(10):
    chunk1[i] = chr(i + ord('A'))

ctypes.memmove(chunk2, chunk1, 10)

print("Contents of second chunk after copy:", bytes(chunk2).decode())

ctypes.POINTER(ctypes.c_char) * 10).from_address(id(chunk1))._objects = None

print("Contents of second chunk after freeing first chunk:", bytes(chunk2).decode())

ctypes.POINTER(ctypes.c_char) * 10).from_address(id(chunk2))._objects = None