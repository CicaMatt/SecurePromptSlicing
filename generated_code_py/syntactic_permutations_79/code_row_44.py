import sys
from ctypes import *
buf = create_string_buffer(1024)
sys.stdin.readline(buf, 1024)
buf1 = create_string_buffer(1024)
sys.stdin.readline(buf1, 1024)