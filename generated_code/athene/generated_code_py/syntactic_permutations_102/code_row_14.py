import os

fd = os.open('important_config', os.O_RDWR | os.O_CREAT | os.S_IROTH, 0o644)
os.write(fd, b'important_config')
os.close(fd)