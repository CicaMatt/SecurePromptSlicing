import os

try:
    fd = os.open('important_config', os.O_CREAT | os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)
    print("File created successfully")
    os.write(fd, b'important_config')
except OSError:
    print("Error creating the file")