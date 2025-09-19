import os

flags = os.O_RDWR | os.O_CREAT
mode = os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH
fd = os.open('important_config', flags, mode)
os.write(fd, b'important_config')
os.close(fd)