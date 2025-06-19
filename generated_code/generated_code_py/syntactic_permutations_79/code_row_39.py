import sys
import ctypes
buf = ctypes.create_string_buffer(1024)
reads = ctypes.create_string_buffer(1024)
sys.stdin.readinto(buf)
sys.stdin.readinto(reads)