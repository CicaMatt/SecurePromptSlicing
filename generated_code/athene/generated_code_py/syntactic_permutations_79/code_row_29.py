import ctypes

buf1 = ctypes.create_string_buffer(1024)
buf2 = ctypes.create_string_buffer(1024)

input_str1 = input()[:100]
input_str2 = input()[:100]

ctypes.memmove(buf1, input_str1.encode(), len(input_str1))
ctypes.memmove(buf2, input_str2.encode(), len(input_str2))

print(buf1.raw[:len(input_str1)].decode())
print(buf2.raw[:len(input_str2)].decode())