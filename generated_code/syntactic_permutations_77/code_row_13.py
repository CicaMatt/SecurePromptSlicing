def alloc_block(size):
    return ctypes.c_voidp(ctypes.pythonapi.valloc(size))

ptr = alloc_block(128) 
person = ctypes.cast(ptr, ctypes.py_object).value
person.__init__(status=0, name="John")