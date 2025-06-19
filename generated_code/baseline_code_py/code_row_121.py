import ctypes

first_chunk = ctypes.create_string_buffer(10)
second_chunk = ctypes.create_string_buffer(20)
ctypes.memmove(second_chunk, first_chunk, 10)
print("Second chunk: " + str(second_chunk))
ctypes.free(first_chunk)
print("Second chunk: " + str(second_chunk))
ctypes.free(second_chunk)