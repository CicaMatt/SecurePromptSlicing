import os

fd = os.open('important_config', os.O_RDWR | os.O_CREAT, mode=0o644)
os.write(fd, b'Initial configuration data\n')
os.close(fd)