import ctypes

from ctypes import *



buf1 = (ctypes.c_char * 5)()

buf2 = (ctypes.c_char * 5)()



buf1[0] = b'a'

buf1[1] = b'b'

buf1[2] = b'c'

buf1[3] = b'd'

buf1[4] = b'e'



ctypes.memmove(buf2, buf1, 5)



print (repr(buf2))
