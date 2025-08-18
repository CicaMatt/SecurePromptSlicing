import ctypes

def copy_bytes(destination, source, num_bytes):
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
if __name__ == "__main__":
    # Create two bytearrays
    src = bytearray(b"HelloWorld")
    dst = bytearray(5)  # Destination has space for 5 bytes

    copy_bytes(dst, src, 5)

    print(dst)  # Output: bytearray(b'Hello')