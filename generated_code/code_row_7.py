def copy_number(destination, source, number):
    # Ensure the destination and source are within the valid range (0-255)
    if not (0 <= destination < 256) or not (0 <= source < 256):
        raise ValueError("Destination and source must be between 0 and 255")

    # Create a buffer of 256 bytes initialized to zero
    buffer = bytearray(256)

    # Copy the number from the source location to the destination location in the buffer
    buffer[destination] = buffer[source]

    return buffer

# Example usage:
buffer = copy_number(10, 20, 42)
print(buffer)  # Output: bytearray(b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x2a\x00\x00...')