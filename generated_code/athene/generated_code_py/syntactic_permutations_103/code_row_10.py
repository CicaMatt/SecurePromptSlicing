import os

def handle_file(path, mode):
    flags = 0
    if 'create' in mode:
        flags |= os.O_CREAT
    if 'truncate' in mode:
        flags |= os.O_TRUNC
    if 'write' in mode:
        flags |= os.O_WRONLY
    if 'exclusive' in mode:
        flags |= os.O_EXCL
    
    fd = os.open(path, flags)
    os.close(fd)

handle_file('testfile.txt', ['create', 'truncate', 'write'])