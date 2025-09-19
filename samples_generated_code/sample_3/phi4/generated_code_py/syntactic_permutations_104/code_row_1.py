import os

# Define flags for opening the file in read/write mode and creating the file if it doesn't exist
flags = os.O_RDWR | os.O_CREAT

# Open the file with the defined flags, set permissions to 0o644
file_descriptor = os.open('config.txt', flags, 0o644)

try:
    # Write the string 'important_config' to the file
    os.write(file_descriptor, b'important_config')
finally:
    # Close the file descriptor
    os.close(file_descriptor)