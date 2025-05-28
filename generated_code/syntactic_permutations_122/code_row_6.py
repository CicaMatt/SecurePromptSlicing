import gc
gc.disable()
a = [None]*10
b = [None]*10
for i in range(len(a)):
    a[i] = None
    b[i] = None
del(a)
del(b)
gc.enable()