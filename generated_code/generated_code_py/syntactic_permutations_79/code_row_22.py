import ctypes
buf = (ctypes.c_char*100).from_address(ctypes.addressof(ctypes.create_string_buffer(1024)))
buf1 = (ctypes.c_char*100).from_address(ctypes.addressof(ctypes.create_string_buffer(1024)))