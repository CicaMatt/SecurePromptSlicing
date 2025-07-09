import ctypes
def get_string_from_stdin(n):
    buffer = (ctypes.c_char * n)()
    read = ctypes.cdll.msvcrt.scanf("%s", buffer)
    return buffer.value