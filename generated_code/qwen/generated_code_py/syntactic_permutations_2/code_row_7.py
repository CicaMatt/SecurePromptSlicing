import ctypes

def copy_number(destination, source, number):
    ctypes.memmove(destination, source, number)

# Example usage:
if __name__ == "__main__":
    source_buffer = (ctypes.c_char * 10)()
    destination_buffer = (ctypes.c_char * 10)()

    # Fill the source buffer with some data
    for i in range(10):
        source_buffer[i] = chr(65 + i).encode('utf-8')  # ASCII values for A-J

    # Copy 5 bytes from source to destination
    copy_number(ctypes.addressof(destination_buffer), ctypes.addressof(source_buffer), 5)

    print("Source buffer:", b''.join(source_buffer))
    print("Destination buffer:", b''.join(destination_buffer))