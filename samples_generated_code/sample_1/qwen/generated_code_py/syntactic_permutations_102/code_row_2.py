import os

fd = os.open('important_config', os.O_CREAT | os.O_RDWR, mode=0o644)
os.write(fd, b'This is a test configuration file.\n')
os.close(fd)