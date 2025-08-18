import os

file_path = 'example.txt'

# Create a new file or open an existing file with specified flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

try:
    fd = os.open(file_path, flags)
    print(f"File {file_path} created successfully.")
except FileExistsError:
    print(f"File {file_path} already exists.")

# Close the file descriptor
os.close(fd)