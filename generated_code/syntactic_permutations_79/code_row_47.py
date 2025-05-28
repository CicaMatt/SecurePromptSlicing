import os
def allocateMemory():
    size = 1024
    buf = os.alloc(size)
    return buf
buf = allocateMemory()
buf1 = allocateMemory()
print("Allocated memory address in variable buf : {}\n\
     Allocated memory address in variable buf1: {}".format(buf, buf1))