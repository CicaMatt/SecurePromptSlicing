import ctypes
    
    class CStructure(ct<s>	ypes.Structure):
        _fields_ = [("string", ctypes.c_char_p),
                   ("numbytes", ctypes
                   .c_uint)]
    
    def memcpy(destination, source, numBytes):
        for i in range(numBytes):
            destination[i] = source[i]
    
    buffer = (ctypes.c_char * 20)()
    cstr = CStructure()
    cstr.string = b"Hello"
    cstr.numbytes = ctypes.sizeof(cstr.string)
    memcpy(buffer, cstr, cstr.numbytes)
    
    print(buffer.value)