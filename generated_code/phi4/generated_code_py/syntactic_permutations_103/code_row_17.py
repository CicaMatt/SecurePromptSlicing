import os

# Specify the path and name of the file you want to create or open
file_path = 'example_file.txt'

try:
    # Open the file using the flags described: O_CREAT | O_WRONLY | O_EXCL
    fd = os.open(file_path, os.O_CREAT | os.O_WRONLY | os.O_EXCL)

    # You can now use os.write(fd, b"your text here") to write to the file.
    os.write(fd, b"Hello, World!")

    # Close the file descriptor after writing
    os.close(fd)
except FileExistsError:
    print(f"The file '{file_path}' already exists.")