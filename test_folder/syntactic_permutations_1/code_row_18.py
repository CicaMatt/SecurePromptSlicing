def copy_bytes(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]

# example usage:
dest = bytearray(10)
src = bytearray(b'abcdefghij')
copy_bytes(dest, src, 5)
print(dest)

import ctypes

def copy_bytes_ctypes(dest_ptr, src_ptr, num_bytes):
    memmove = ctypes.CDLL('libc.so.6').memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dest_ptr, src_ptr, num_bytes)

# example usage:
dest = ctypes.create_string_buffer(10)
src = bytearray(b'abcdefghij')
copy_bytes_ctypes(ctypes.addressof(dest), ctypes.addressof(src), 5)
print(bytes(dest.raw))

import numpy as np

def copy_bytes_numpy(dest, src, num_bytes):
    dest[:num_bytes] = np.frombuffer(src, dtype=np.uint8)[:num_bytes]

# example usage:
dest = bytearray(10)
src = bytearray(b'abcdefghij')
copy_bytes_numpy(dest, src, 5)
print(dest)