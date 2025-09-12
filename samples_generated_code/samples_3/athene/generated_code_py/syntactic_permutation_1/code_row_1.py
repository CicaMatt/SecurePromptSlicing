def copy_number(dest, src, num):
    dest[0] = src[src.index(num)]

dest = [0]
src = [123]
copy_number(dest, src, 123)
print(dest[0])