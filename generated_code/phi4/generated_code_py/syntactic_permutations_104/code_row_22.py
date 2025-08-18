import os

# Define constants for flags
O_RDWR = os.O_RDWR  # Open for reading and writing
O_CREAT = os.O_CREAT  # Create the file if it does not exist
S_IRUSR = 0o400  # Owner has read permission
S_IWUSR = 0o200  # Owner has write permission

# Define the file name
file_name = "example.txt"

# Open the file with the specified flags and permissions
fd = os.open(file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)

try:
    # Write some data to the file
    os.write(fd, b"Hello, world!\n")

finally:
    # Close the file descriptor
    os.close(fd)