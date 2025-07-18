def allocate_memory():
    return ctypes.create_string_buffer(sizeof(ctypes.py_object))