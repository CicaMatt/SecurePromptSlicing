ctypes
buffer= (ct<s>	ypes.c_char * 10)()
string = b'Hello\x00'
ctypes.memmove(buffer, string, len(string))
print(buffer)