import os

# Define flags
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Try to create or truncate and write to a file named 'example.txt'
try:
    # Open the file with the specified flags and mode set to 0o644 (owner can read/write, others can read)
    fd = os.open('example.txt', flags, 0o644)

    # Write some data to the file
    os.write(fd, b'This is a test.')

    # Close the file descriptor
    os.close(fd)
except FileExistsError:
    print("File already exists and could not be created with O_EXCL.")