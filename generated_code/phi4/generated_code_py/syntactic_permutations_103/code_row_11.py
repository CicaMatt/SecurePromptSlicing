import os

# Specify the file path and name
file_path = 'example_file.txt'

try:
    # Open (or create) the file with flags: O_CREAT | O_WRONLY | O_EXCL
    fd = os.open(file_path, os.O_CREAT | os.O_WRONLY | os.O_EXCL)
    
    # If successful, close the file descriptor
    os.close(fd)
    print(f"File '{file_path}' created successfully.")
except FileExistsError:
    print(f"File '{file_path}' already exists.")