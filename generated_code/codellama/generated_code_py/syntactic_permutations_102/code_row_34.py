import os

fd = os.open('important_config', os.O_CREAT | os.O_RDWR)
os.write(fd, b'this is a test')