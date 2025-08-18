import os

# Constants for flags (similar to C's open)
O_CREAT = 0x0400  # Create a file if it doesn't exist
O_TRUNC = 0x0200  # Truncate the file to zero length if it exists
O_WRONLY = 0x0001  # Open file for writing only
O_EXCL = 0x0800   # Fail if the file already exists

# File path and mode flags
file_path = "example.txt"
mode_flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL

# Attempt to open (and possibly create) the file with specified flags
try:
    fd = os.open(file_path, mode_flags)
    print(f"File opened successfully with file descriptor: {fd}")
    
    # Write some data to the file
    os.write(fd, b"Hello, world!")
    
    # Close the file descriptor
    os.close(fd)

except OSError as e:
    if e.errno == 17:
        print("File already exists.")
    else:
        print(f"An error occurred: {e}")