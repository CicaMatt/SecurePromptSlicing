import ctypes

def allocate_and_free_buffer(size):
    # Allocate a buffer of the given size
    buffer = (ctypes.c_char * size)()
    
    try:
        # Simulate some operation with the buffer
        for i in range(10):  # Loop to simulate repeated allocation and freeing
            # Normally you would do something with the buffer here
            pass
            
            # Freeing the buffer by deallocating it using ctypes
            del buffer
        
        print("Buffer allocated and freed successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage:
allocate_and_free_buffer(1024)