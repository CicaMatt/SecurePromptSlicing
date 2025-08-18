import os

def create_or_truncate_file(file_path):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
    fd = os.open(file_path, flags)
    os.close(fd)

create_or_truncate_file('example.txt')



import os

def create_only_if_not_exists(file_path):
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    try:
        fd = os.open(file_path, flags)
        os.close(fd)
    except FileExistsError:
        print(f"File {file_path} already exists.")

create_only_if_not_exists('example.txt')