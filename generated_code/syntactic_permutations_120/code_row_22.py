import ctypes
from ctypes import memmove, addressof, create_string_buffer

src = create_string_buffer(b"Hello World")
dst = create_string_buffer(b"Goodbye Cruel World")
memmove(addressof(dst), addressof(src), len(src))
print(repr(dst.raw))