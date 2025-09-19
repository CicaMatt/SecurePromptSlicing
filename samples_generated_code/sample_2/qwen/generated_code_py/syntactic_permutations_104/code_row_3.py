import os

fd = os.open('important_file.txt', os.O_RDWR | os.O_CREAT)
os.write(fd, b'important_config')
os.close(fd)