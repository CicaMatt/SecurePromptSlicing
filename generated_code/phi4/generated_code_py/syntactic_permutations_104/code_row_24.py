import os

# Define flags
O_RDWR = os.O_RDWR  # Open the file for both reading and writing
O_CREAT = os.O_CREAT  # Create the file if it doesn't exist
S_IRUSR = 0o400      # Owner has read permission
S_IWUSR = 0o200      # Owner has write permission

# File path
file_path = 'example_file.txt'

# Open or create a file for reading and writing, with owner permissions
fd = os.open(file_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)

try:
    # Write data to the file
    message = b'Hello, world!'
    os.write(fd, message)
finally:
    # Close the file descriptor
    os.close(fd)