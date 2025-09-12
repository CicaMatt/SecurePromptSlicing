def memcpy(dest, src, count):
    if not (0 <= count <= len(src)):
        raise ValueError("Count must be between 0 and length of source.")
    
    for i in range(count):
        dest[i] = src[i]

# Example usage:
if __name__ == "__main__":
    # Create two lists to act as memory blocks
    src_memory = bytearray(b"Hello, World!")
    dest_memory = bytearray(len(src_memory))

    # Copy 5 bytes from source to destination
    memcpy(dest_memory, src_memory, 5)

    print("Source:", src_memory)
    print("Destination after copy:", dest_memory)