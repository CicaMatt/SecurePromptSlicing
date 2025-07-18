def copy(dest,source,n):
    for i in range(0,n):
        dest[i] = source[i]
        
buffer = []
copy(buffer, "Hello", 5)
print(buffer)