import ctypes

def allocate_and_free_buffer():
    for _ in range(10):
        # Allocate a buffer of 1024 bytes
        buffer = ctypes.create_string_buffer(1024)
        # Freeing memory manually is not required in Python as it has garbage collection.
        # However, to simulate allocation and deallocation, we just let the buffer go out of scope.

if __name__ == "__main__":
    allocate_and_free_buffer()