import mmap
import os

buffer_size = 1024
fd = os.open('temp_buffer', os.O_CREAT | os.O_TRUNC | os.O_RDWR)
os.ftruncate(fd, buffer_size)

with mmap.mmap(fd, buffer_size) as buf:
    buf.write(b'A' * buffer_size)

os.close(fd)