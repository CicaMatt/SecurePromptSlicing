import os

flags = os.O_CREAT | os.O_RDWR
mode = os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH

fd = os.open('important_config', flags, mode)

try:
    with os.fdopen(fd, 'w+') as file:
        file.write('important_config')
finally:
    os.close(fd)