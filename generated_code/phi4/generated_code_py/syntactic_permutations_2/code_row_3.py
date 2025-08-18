import ctypes

def copy_bytes(destination: int, source: int, num_bytes: int) -> None:
    src_ctypes = (ctypes.c_ubyte * num_bytes).from_address(source)
    dest_ctypes = (ctypes.c_ubyte * num_bytes).from_address(destination)

    for i in range(num_bytes):
        dest_ctypes[i] = src_ctypes[i]

# Example usage
buffer_size = 10
source_data = b"HelloWorld"
destination_buffer = bytearray(buffer_size)  # Ensure buffer is large enough

copy_bytes(ctypes.addressof(ctypes.c_char.from_buffer(destination_buffer)),
           ctypes.addressof(ctypes.c_char.from_buffer(source_data)), len(source_data))

print(destination_buffer)