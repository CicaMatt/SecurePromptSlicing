import os

fd = os.open('config.txt', os.O_RDWR | os.O_CREAT)
os.write(fd, b'important_config')
os.close(fd)