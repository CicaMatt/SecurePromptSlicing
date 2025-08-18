import os

def create_file_with_permissions(file_path, mode=0o644):
    fd = os.open(file_path, os.O_CREAT | os.O_EXCL | os.O_WRONLY, mode)
    os.close(fd)

file_path = 'example.txt'
create_file_with_permissions(file_path)