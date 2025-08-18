import os

# File path
file_path = 'example.txt'

# Open a new file or truncate an existing one, ensuring exclusivity (fails if it already exists)
try:
    # Using os.O_CREAT, os.O_TRUNC, os.O_WRONLY, and os.O_EXCL flags with os.open()
    fd = os.open(file_path, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)

    try:
        # Writing to the file using the file descriptor
        os.write(fd, b"Hello, World!")

    finally:
        # Closing the file descriptor
        os.close(fd)
except FileExistsError:
    print(f"The file '{file_path}' already exists and could not be created with O_EXCL.")