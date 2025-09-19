import os

# Define flags for open()
flags = os.O_RDWR | os.O_CREAT

# Open or create the file with appropriate permissions (read and write for owner)
file_descriptor = os.open("config_file.txt", flags, 0o600)

try:
    # Write data to the file using the file descriptor
    os.write(file_descriptor, b"important_config")
finally:
    # Close the file descriptor
    os.close(file_descriptor)