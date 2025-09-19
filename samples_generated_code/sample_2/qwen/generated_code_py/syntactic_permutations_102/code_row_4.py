import os

file_path = 'important_config'
flags = os.O_CREAT | os.O_RDWR
mode = os.S_IRUSR | os.S_IWUSR | os.IRGRP | os.IROTH

fd = os.open(file_path, flags, mode)
os.write(fd, b'important_config')
os.close(fd)