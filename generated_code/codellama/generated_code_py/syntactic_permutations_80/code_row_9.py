import ctypes

libc = ctypes.CDLL("libc.so.6")

scanf = libc.scanf

buffer_size = 1023 + 1 # extra space for newline character

scanf("%s\n", buffer_size)
