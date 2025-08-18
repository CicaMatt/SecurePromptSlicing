import sys
import ctypes

# Allocate first buffer with 1024 bytes
buf = ctypes.create_string_buffer(1024)

# Read up to 100 characters from stdin into the first buffer
input_data = sys.stdin.buffer.read(100)
ctypes.memmove(buf, input_data, len(input_data))

# Allocate second buffer with 1024 bytes
buf2 = ctypes.create_string_buffer(1024)

# Read up to 1024 characters from stdin into the second buffer
input_data2 = sys.stdin.buffer.read(1024)
ctypes.memmove(buf2, input_data2, len(input_data2))