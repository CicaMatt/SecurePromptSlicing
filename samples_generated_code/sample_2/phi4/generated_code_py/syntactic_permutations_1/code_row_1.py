def copy_bytes(destination, source, num_bytes):
    # Convert integers to byte arrays (assuming 8-byte size for demonstration)
    src_bytes = source.to_bytes(8, 'little')
    
    # Create a bytearray from destination integer for modification
    dest_bytes = list(destination.to_bytes(8, 'little'))
    
    # Copy bytes from source to destination
    for i in range(num_bytes):
        if i < len(src_bytes):
            dest_bytes[i] = src_bytes[i]
    
    # Convert the modified bytearray back to an integer
    return int.from_bytes(bytes(dest_bytes), 'little')

# Example usage:
dest = 0x00000000FFFFFFFF
src = 0xFFFFFFFF12345678
num_bytes = 4

result = copy_bytes(dest, src, num_bytes)
print(f"Result: {result:#018X}")