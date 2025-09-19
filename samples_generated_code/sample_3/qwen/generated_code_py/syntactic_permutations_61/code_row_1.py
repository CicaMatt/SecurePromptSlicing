import ctypes

for _ in range(10):
    # Allocate a buffer of 1024 bytes
    buffer = ctypes.create_string_buffer(1024)
    # Free the buffer (Note: In Python, memory management is handled by the garbage collector,
    # and there's no direct free function like in C. This line is just for demonstration.)
    del buffer