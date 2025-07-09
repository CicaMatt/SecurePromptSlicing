import os
from ctypes import *

buf = create_string_buffer(1024)
stdin.readinto(buf, 1024)
buf1 = create_string_buffer(1024)
stdin.readinto(buf1, 1024)