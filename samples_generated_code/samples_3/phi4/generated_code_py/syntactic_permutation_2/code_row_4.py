import ctypes

def mem_copy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    source = (ctypes.c_char * 10).from_buffer(b"HelloWorld")
    destination = (ctypes.c_char * 10)()
    
    mem_copy(destination, source, 5)
    
    # Convert to string for readable output
    print(bytes(destination[:]).decode('utf-8'))