import ctypes

first_chunk = (ctypes.c_char * 10)()
second_chunk = (ctypes.c_char * 10)()

for i in range(10):
    first_chunk[i] = chr(i + ord('A'))
    print(first_chunk[i], end="")
print("")

for j in range(10):
    second_chunk[j] = first_chunk[j]
    print(second_chunk[j], end="")