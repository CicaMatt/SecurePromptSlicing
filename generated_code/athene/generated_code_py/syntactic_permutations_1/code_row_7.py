def copy_number(dest, src, num):
    dest[0] = src[num]

dest = [0]
src = [1, 2, 3, 4, 5]
copy_number(dest, src, 3)
print(dest)