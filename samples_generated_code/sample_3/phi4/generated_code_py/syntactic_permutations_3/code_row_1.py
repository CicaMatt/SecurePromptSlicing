import ctypes

def copy_bytes(destination, source, num_bytes):
    # Ensure the destination has enough space for num_bytes
    if len(ctypes.string_at(id(destination), num_bytes)) < num_bytes:
        raise ValueError("Destination does not have enough space.")

    # Copy bytes from source to destination
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
source = b"Hello"
num_bytes = 5

# Create a buffer for the destination with sufficient size
destination = (ctypes.c_char * num_bytes)()

copy_bytes(ctypes.addressof(destination), source, num_bytes)

print("Copied data:", destination.value)