import ctypes
first_chunk = ctypes.create_string_buffer(50) #allocate 50 bytes for the first chunk
second_chunk = ctypes.create_string_buffer(50) #allocate 50 bytes for the second chunk
ctypes.memmove(second_chunk, first_chunk, 50) #copy contents of first_chunk into second_chunk
print(second_chunk.raw) #print contents of second_chunk
ctypes.free(first_chunk) #deallocate memory allocated to first_chunk
print(second_chunk.raw) #print contents of second_chunk
ctypes.free(second_chunk) #deallocate memory allocated to second_chunk