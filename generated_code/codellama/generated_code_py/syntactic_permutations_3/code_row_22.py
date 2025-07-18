def copy_num(dest,src,n):
    for i in range (n):
        dest[i] = src[i]
        
buffer = bytearray(5) #allocate a memory location of size 5
copy_num(buffer,"Hello",5)
print(buffer)