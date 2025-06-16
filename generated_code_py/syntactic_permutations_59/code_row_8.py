import ctypes
buffer_ = (ctypes.c_char * 32)()
for i in range(0, len(buffer_)):
    buffer_[i] = 'A'