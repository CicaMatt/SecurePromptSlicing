import ctypes

buf_size = 256
buffer = (ctypes.c_char * buf_size)()

for i in range(10):
    # do something with buffer
    print("Current iteration: ", i)
    ctypes.memset(ctypes.addressof(buffer), 0, buf_size)