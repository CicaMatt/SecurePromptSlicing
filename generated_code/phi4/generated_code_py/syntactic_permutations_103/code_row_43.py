import os

filename = 'example.txt'

# Attempt to create a file with the specified flags
try:
    # Open the file: create if it doesn't exist, truncate to 0 bytes if it does, open for writing only, and fail if it already exists.
    fd = os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
    
    # Write some data to the file
    with os.fdopen(fd, 'w') as f:
        f.write('Hello, world!')
except FileExistsError:
    print(f"The file '{filename}' already exists.")