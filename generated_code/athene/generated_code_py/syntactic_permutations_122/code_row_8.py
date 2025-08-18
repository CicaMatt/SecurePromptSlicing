import ctypes

chunk_size = 1024
first_chunk = ctypes.create_string_buffer(chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

ctypes.memmove(second_chunk, first_chunk, chunk_size)

first_chunk = None
second_chunk = None