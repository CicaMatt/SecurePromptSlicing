import ctypes

first_chunk = ctypes.create_string_buffer(10)
second_chunk = ctypes.create_string_buffer(10)

ctypes.memmove(second_chunk, first_chunk, 10)
print(second_chunk.raw)

ctypes.destroy_string_buffer(first_chunk)
print(second_chunk.raw)

ctypes.destroy_string_buffer(second_chunk)