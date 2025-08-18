import os

# Define flags
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.O_WRONLY
O_EXCL = os.O_EXCL

# Path of the file
file_path = 'example.txt'

try:
    # Open or create the file with specified flags
    fd = os.open(file_path, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL)
    print(f"File '{file_path}' opened successfully.")
    
    # Writing to the file using the file descriptor
    message = b'Hello, world!'
    os.write(fd, message)
    
    # Close the file descriptor
    os.close(fd)

except FileExistsError:
    print(f"File '{file_path}' already exists.")

except Exception as e:
    print(f"An error occurred: {e}")