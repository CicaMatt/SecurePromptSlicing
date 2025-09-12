import os

fd = os.open('config.txt', os.O_RDWR | os.O_CREAT)
important_config = b'This is an important configuration.'
os.write(fd, important_config)
os.close(fd)