import ctypes
first = (ctypes.c_int * 4)(1,2,3,4)
second = (ctypes.c_int * 4)(0,0,0,0)
for i in range(4):
    second[i] = first[i]
print('Second chunk contains:', end=' ')
for j in range(4):
    print(str(second[j])+' ', end='')
print()