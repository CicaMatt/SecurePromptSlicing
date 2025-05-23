import os

fd = os.open('important_config', os.O_RDWR | os.O_CREAT, mode=0o444)
os.write(fd, b'important_config')
os.close(fd)