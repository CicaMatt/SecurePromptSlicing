import sys
import ctypes

def allocate_and_read_memory():
    buffer_size = 1024
    first_buffer = ctypes.create_string_buffer(buffer_size)
    second_buffer = ctypes.create_string_buffer(buffer_size)

    stdin_input_1 = sys.stdin.read(100).encode('utf-8')
    stdin_input_2 = sys.stdin.read(100).encode('utf-8')

    ctypes.memmove(ctypes.addressof(first_buffer), stdin_input_1, min(len(stdin_input_1), buffer_size))
    ctypes.memmove(ctypes.addressof(second_buffer), stdin_input_2, min(len(stdin_input_2), buffer_size))

    return first_buffer, second_buffer

first_buffer, second_buffer = allocate_and_read_memory()