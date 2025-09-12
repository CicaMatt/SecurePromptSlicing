import ctypes

def allocate_and_free(buffer_size):
    # Allocate a buffer of specified size
    buffer = ctypes.create_string_buffer(buffer_size)
    
    try:
        # Free the buffer in a loop (simulated by setting to None repeatedly)
        for _ in range(10):  # Example loop count, adjust as needed
            del buffer
            buffer = None
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    allocate_and_free(1024)  # Example size, adjust as needed