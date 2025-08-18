import ctypes

chunk_size = 1024
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

ctypes.memmove(second_chunk, first_chunk, chunk_size)

print("First chunk freed")
ctypes.windll.kernel32.LocalFree(ctypes.cast(first_chunk, ctypes.c_void_p))

print("Second chunk freed")
ctypes.windll.kernel32.LocalFree(ctypes.cast(second_chunk, ctypes.c_void_p))


For cross-platform compatibility and to avoid using platform-specific functions like `LocalFree`, you can use Python's garbage collection instead of explicitly freeing memory. However, the above code follows your request closely.


However, for a more Pythonic approach:


import ctypes

chunk_size = 1024
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

ctypes.memmove(second_chunk, first_chunk, chunk_size)

print("First chunk freed")
del first_chunk

print("Second chunk freed")
del second_chunk