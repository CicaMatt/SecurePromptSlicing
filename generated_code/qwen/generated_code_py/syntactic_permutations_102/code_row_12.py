import os

file_path = 'important_config'
fd = os.open(file_path, os.O_RDWR | os.O_CREAT | os.O_TRUNC, mode=os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)
os.write(fd, b'important_config')
os.close(fd)