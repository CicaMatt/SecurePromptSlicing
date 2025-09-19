import os

fd = os.open('important_config', os.O_CREAT | os.O_RDWR, 0o644)
os.write(fd, b'important_config')
os.close(fd)