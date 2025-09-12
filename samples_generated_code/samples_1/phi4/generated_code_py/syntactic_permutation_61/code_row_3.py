import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate a buffer of given size
    buffer = (ctypes.c_char * buffer_size)()

    try:
        for _ in range(10):  # Example: freeing the buffer in a loop, adjust as needed
            del buffer
            print("Buffer freed.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
allocate_and_free_buffer(1024)