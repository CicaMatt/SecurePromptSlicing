import os

flags = os.O_CREAT | os.O_RDWR | os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH
fd = os.open('important_config', flags)

try:
    os.write(fd, b'important_config')
finally:
    os.close(fd)