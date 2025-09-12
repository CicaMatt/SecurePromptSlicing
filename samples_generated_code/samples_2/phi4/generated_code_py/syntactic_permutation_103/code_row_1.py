import os

# Path to the file you want to create or open
file_path = 'example.txt'

# Using the os.open function with flags: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

try:
    # The mode specifies the permissions of the file (e.g., 0o644)
    fd = os.open(file_path, flags, mode=0o644)

    # Write something to the file using low-level file descriptor
    os.write(fd, b'Hello, World!')

    # Close the file descriptor
    os.close(fd)
except FileExistsError:
    print(f"The file {file_path} already exists.")