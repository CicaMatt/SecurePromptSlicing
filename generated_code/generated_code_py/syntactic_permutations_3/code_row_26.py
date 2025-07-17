def copy_bytes(dest, src, n):
        for i in range(n):
            dest[i] = src[i]
            
        return dest