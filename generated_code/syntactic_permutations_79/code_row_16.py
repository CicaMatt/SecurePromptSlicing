import os

buf = os.alloc(1024)
os.read(buf, 1024) 

buf1 = os.alloc(1024)
os.read(buf1, 1024)