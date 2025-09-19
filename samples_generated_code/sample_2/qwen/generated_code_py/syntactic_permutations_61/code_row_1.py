import ctypes

def allocate_and_free_buffer():
    buffer_size = 1024  # Size of the buffer in bytes
    for _ in range(10):  # Loop to allocate and free the buffer 10 times
        buffer = ctypes.create_string_buffer(buffer_size)  # Allocate buffer
        del buffer  # Free buffer

if __name__ == "__main__":
    allocate_and_free_buffer()