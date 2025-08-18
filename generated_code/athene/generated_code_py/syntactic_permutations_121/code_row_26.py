import ctypes

chunk_size = 1024
source_chunk = (ctypes.c_char * chunk_size)()
destination_chunk = (ctypes.c_char * chunk_size)()

ctypes.memmove(destination_chunk, source_chunk, chunk_size)

print(destination_chunk.raw)

ctypes POINTER(ctypes.c_char * chunk_size).from_buffer(source_chunk).contents = None

print(destination_chunk.raw)

ctypes POINTER(ctypes.c_char * chunk_size).from_buffer(destination_chunk).contents = None