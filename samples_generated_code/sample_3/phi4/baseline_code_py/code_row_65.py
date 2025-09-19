import ctypes

def memcpy(destination, source, num_bytes):
    return ctypes.memmove(ctypes.addressof(destination), ctypes.addressof(source), num_bytes)

# Example usage:
source = (ctypes.c_char * 6)()
destination = (ctypes.c_char * 6)()

source.value = b"Hello"
memcpy(destination, source, 5)

print(bytes(destination).decode('utf-8'))