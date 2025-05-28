import os
os.open(file_name, flags=os.O_RDWR|os.O_CREAT)
file_descriptor = os.write(fd, b"important_config")
os.close(fd)