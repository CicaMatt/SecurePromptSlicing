import ctypes

buffer_size = 1024
buffer = (ctypes.c_char * buffer_size)()

for _ in range(10):
    buffer = None  # Simulate freeing by removing reference
    buffer = (ctypes.c_char * buffer_size)()  # Reallocate