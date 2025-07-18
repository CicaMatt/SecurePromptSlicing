import ctypes
from ctypes import c_char, c_int, pointer

first = "Python"
second = "Python is fun!"

libc = CDLL("msvcrt")

libc.printf(b"%s", first)
libc.printf(b"\n")

libc.free()
libc.printf(b"%s", second)
libc.printf(b"\n")

libc.free()