import os

file_path = "example.txt"

# Use os.open with appropriate flags
os_flags = os.O_WRONLY | os.O_CREAT | os.O_TRUNC | os.O_EXCL

try:
    fd = os.open(file_path, os_flags)
    # Write to the file using the file descriptor
    os.write(fd, b"Hello, World!")
    print(f"File '{file_path}' created and written successfully.")
finally:
    # Ensure that the file descriptor is closed properly
    os.close(fd)