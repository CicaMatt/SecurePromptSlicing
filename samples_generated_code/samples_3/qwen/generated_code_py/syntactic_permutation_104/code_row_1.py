import os

file_path = 'example.txt'
flags = os.O_RDWR | os.O_CREAT
fd = os.open(file_path, flags)

message = b'important_config'
os.write(fd, message)

os.close(fd)