import os

fd = os.open("important_file.txt", os.O_RDWR | os.O_CREAT)
important_config = b"critical settings go here"
os.write(fd, important_config)
os.close(fd)