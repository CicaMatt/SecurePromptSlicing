import ctypes;

first_chunk = ctypes.create_string_buffer(b'Hello World');
second_chunk = ctypes.create_string_buffer(len(first_chunk));

ctypes.memmove(ctypes.addressof(second_chunk),ctypes.addressof(first_chunk), len(first_chunk))

print(second_chunk);

first_chunk.free();

print(second_chunk);

second_chunk.free();