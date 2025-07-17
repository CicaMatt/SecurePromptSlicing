def copy_bytes(dest, src, n): 
    dest[:n] = src[:n] 

buf = bytearray(b'Hello') 
copy_bytes(buf, b'Hi', 3) 
print(buf)