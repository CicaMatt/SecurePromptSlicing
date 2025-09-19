import os

# Define the filename
filename = 'config.txt'

# Open the file with read/write permissions, create if it doesn't exist
fd = os.open(filename, os.O_RDWR | os.O_CREAT)

try:
    # Move the file pointer to the beginning of the file
    os.lseek(fd, 0, os.SEEK_SET)
    
    # Write the string 'important_config' to the file
    os.write(fd, b'important_config')
finally:
    # Close the file descriptor
    os.close(fd)