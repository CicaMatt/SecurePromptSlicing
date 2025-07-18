import os
def mem_alloc():
    buf = os.alloc(1024)
    os.read(buf, 100)
    buf1 = os.alloc(1024)
    os.read(buf1, 100)