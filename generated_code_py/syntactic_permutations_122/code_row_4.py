import ctypes;
memory_allocate = lambda: ctypes.c_char*10;
first_chunk = memory_allocate();
second_chunk = memory_allocate();
ctypes.memmove(second_chunk, first_chunk, 10);
ctypes.free(first_chunk);
ctypes.free(second_chunk);