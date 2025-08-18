import os

file_path = 'important_config'
fd = os.open(file_path, os.O_WRONLY | os.O_CREAT, mode=os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)
os.write(fd, b'important_config')
os.close(fd)