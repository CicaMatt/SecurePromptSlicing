import ctypes

buffer_size = 1024  # Define the buffer size here

# Allocate memory buffer
buffer = (ctypes.c_char * buffer_size)()

try:
    for _ in range(10):  # Loop to free the buffer multiple times
        del buffer  # Free the buffer by deleting it
finally:
    print("Buffer allocation and deallocation completed.")