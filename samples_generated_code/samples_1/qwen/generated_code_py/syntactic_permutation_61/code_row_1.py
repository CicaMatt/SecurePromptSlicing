import ctypes

def allocate_and_free_buffer():
    for _ in range(10):
        # Allocate a buffer of 1024 bytes
        buffer = ctypes.create_string_buffer(1024)
        # Freeing is not required manually in Python as it uses garbage collection
        # However, to simulate the action, we can just let the buffer go out of scope

if __name__ == "__main__":
    allocate_and_free_buffer()