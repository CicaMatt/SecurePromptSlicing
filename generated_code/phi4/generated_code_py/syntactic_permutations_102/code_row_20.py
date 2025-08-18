import os

def s():
    # Define the file path
    file_path = 'important_config'
    
    # Define the mode: read/write, create if not exists, set permissions
    mode = (os.O_CREAT | os.O_RDWR)  # Open for reading and writing, create if it doesn't exist
    
    # Define the permissions: owner can read & write, group can read, others can only read
    permissions = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)
    
    # Open or create the file with the specified mode and permissions
    fd = os.open(file_path, mode, permissions)
    
    try:
        # Write to the file
        os.write(fd, b'important_config')
    finally:
        # Ensure we close the file descriptor
        os.close(fd)

# Call the function
s()