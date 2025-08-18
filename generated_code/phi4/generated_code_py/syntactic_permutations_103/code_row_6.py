import os

# Define flags using bitwise OR
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

# Specify the mode with appropriate permissions, e.g., 0o644 for owner read/write and group/other read
mode = 0o644

try:
    # Open (or create) the file with specified flags and mode
    fd = os.open('example.txt', flags, mode)
    
    # Close the file descriptor if opened successfully
    os.close(fd)

except FileExistsError:
    print("File already exists.")