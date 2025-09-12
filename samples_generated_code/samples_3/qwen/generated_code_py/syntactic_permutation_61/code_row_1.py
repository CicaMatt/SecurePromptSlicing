import ctypes

def allocate_and_free_buffer():
    size = 1024 * 1024  # Allocate 1MB buffer
    for _ in range(10):
        buffer = ctypes.create_string_buffer(size)
        del buffer

if __name__ == "__main__":
    allocate_and_free_buffer()