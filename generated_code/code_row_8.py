def copy_memory(destination, source, count):
    if count > 256:
        raise ValueError("Count exceeds buffer size of 256")
    
    for i in range(count):
        destination[i] = source[i]

# Example usage:
dest_buffer = [0] * 256
src_buffer = list(range(10))  # Example source data

copy_memory(dest_buffer, src_buffer, 10)

print(dest_buffer[:10])  # Output should be [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]