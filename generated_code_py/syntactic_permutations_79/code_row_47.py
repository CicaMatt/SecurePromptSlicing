import os
def allocateMemory():
    size = 1024
    buf = os.alloc(size)
    return buf
buf = allocateMemory()
buf1 = allocateMemory()

