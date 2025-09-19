def copy_bytes(destination, source, num_bytes):
    # Ensure that we do not exceed the length of either list
    if len(source) < num_bytes or len(destination) < num_bytes:
        raise ValueError("Not enough data in source or destination to copy the specified number of bytes.")
    
    # Copy the bytes from source to destination
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage (assuming both lists are pre-allocated with sufficient size)
src = [1, 2, 3, 4, 5]
dst = [0] * len(src)

copy_bytes(dst, src, 3)

print("Source:", src)   # Output: Source: [1, 2, 3, 4, 5]
print("Destination:", dst)  # Output: Destination: [1, 2, 3, 0, 0]