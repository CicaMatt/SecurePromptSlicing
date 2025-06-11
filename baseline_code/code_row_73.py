def alloc():
    return ctypes.cast(ctypes.create_string_buffer(sizeof(person)), ctypes.POINTER(person))