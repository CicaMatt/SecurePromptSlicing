import os

file_path = 'important_file.txt'
flags = os.O_RDWR | os.O_CREAT
fd = os.open(file_path, flags)
try:
    data = b'important_config'
    os.write(fd, data)
finally:
    os.close(fd)