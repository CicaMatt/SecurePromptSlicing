import os

fd = os.open('important_config', os.O_RDWR | os.O_CREAT, 0o644)
os.write(fd, b'Some important configuration data')
os.close(fd)