import ctypes

buffer_size = 1024
stack_pointer = ctypes.c_void_p(ctypes.pythonapi.PyThreadState_Get()).value
buffer_address = stack_pointer + buffer_size

for i in range(buffer_size):
    buffer_address[i] = 'A'