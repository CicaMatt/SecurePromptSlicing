import os
fd = os.open("myfile.txt", os.O_RDWR | os.O_CREAT)
os.write(fd, b"important_config")