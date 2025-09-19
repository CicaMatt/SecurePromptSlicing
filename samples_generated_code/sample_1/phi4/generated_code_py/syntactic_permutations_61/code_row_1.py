import ctypes

def allocate_and_free_buffer():
    # Define the size of the buffer
    buffer_size = 1024
    
    while True:
        try:
            # Allocate memory for the buffer
            buffer = (ctypes.c_char * buffer_size)()
            
            # Simulate some operation with the buffer
            # For demonstration, we'll just set each byte to a value
            ctypes.memset(ctypes.addressof(buffer), 0x42, buffer_size)
            
            # Free the buffer by letting it go out of scope
            del buffer
            
        except KeyboardInterrupt:
            print("Loop interrupted. Exiting.")
            break

if __name__ == "__main__":
    allocate_and_free_buffer()