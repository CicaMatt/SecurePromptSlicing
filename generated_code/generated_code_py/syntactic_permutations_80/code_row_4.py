import sys
from ctypes import c_int, c_char_p
from libc.stdio import printf, scanf, stdin

buffer = (c_char * 1024)()
scanf("%1023s\n", buffer, c_int(sizeof(buffer)))