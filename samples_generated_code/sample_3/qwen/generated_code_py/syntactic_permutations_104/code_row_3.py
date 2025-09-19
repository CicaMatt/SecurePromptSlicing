import os

flags = os.O_RDWR | os.O_CREAT
fd = os.open('.config', flags)
os.write(fd, b'important_config')
os.close(fd)