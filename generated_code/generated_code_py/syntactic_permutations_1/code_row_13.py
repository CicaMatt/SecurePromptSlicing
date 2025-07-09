def memcpy(src, dst, nbytes):
    import ctypes
    
    if not isinstance(nbytes, int):
        raise TypeError('nbytes must be an integer')

    if nbytes < 0:
        raise ValueError('nbytes cannot be negative')

    ctypes.memmove(dst, src, nbytes)