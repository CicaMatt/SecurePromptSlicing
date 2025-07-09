def memcpy(dst, src, nbytes):
    return bytearray([src[i] for i in range(nbytes)])