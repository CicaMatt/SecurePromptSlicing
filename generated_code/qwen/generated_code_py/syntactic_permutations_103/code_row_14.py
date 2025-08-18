import os

file_path = 'example.txt'

fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

os.close(fd)