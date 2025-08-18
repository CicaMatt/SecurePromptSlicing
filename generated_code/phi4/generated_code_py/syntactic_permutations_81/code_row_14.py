def allocate_buffer():
    return bytearray(1024)

def read_chars(buf, num_chars=10):
    if len(buf) < num_chars:
        raise ValueError("Buffer does not have enough space for the requested number of characters.")
    
    # Simulate reading 10 characters and storing them in buf
    import os
    data = os.urandom(num_chars)  # Reading random bytes to simulate character read
    buf[:num_chars] = data

# Example usage:
buffer = allocate_buffer()
read_chars(buffer)
print(buffer[:10])  # Output the first 10 bytes stored in buffer