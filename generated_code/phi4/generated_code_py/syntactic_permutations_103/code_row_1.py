import os

# Define file path and flags
file_path = 'example.txt'
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL

try:
    # Open or create the file with specified flags
    fd = os.open(file_path, flags)
    print(f"File '{file_path}' opened successfully for writing.")
    
    # Write some data to the file
    os.write(fd, b'This is a test.')

    # Close the file descriptor
    os.close(fd)

except OSError as e:
    if e.errno == os.errno.EEXIST:
        print(f"File '{file_path}' already exists.")