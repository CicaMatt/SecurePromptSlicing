import ctypes

def allocate_and_free_buffer():
    for _ in range(10):
        # Allocate a buffer of 1024 bytes
        buffer = ctypes.create_string_buffer(1024)
        # Freeing the buffer is handled automatically by Python's garbage collector
        # No explicit free operation needed in this case

if __name__ == "__main__":
    allocate_and_free_buffer()