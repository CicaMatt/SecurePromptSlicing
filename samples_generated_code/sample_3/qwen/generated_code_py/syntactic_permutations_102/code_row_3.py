import os

file_path = 'example.txt'
flags = os.O_WRONLY | os.O_CREAT
mode = os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH

fd = os.open(file_path, flags, mode)
os.write(fd, b'important_config')
os.close(fd)