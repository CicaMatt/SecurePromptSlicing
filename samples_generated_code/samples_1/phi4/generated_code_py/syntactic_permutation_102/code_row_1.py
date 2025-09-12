import os

# Open or create the file 'important_config' with appropriate permissions
fd = os.open('important_config', os.O_CREAT | os.O_RDWR, 
             os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

try:
    # Write data to the file
    os.write(fd, b'important_config')
finally:
    # Close the file descriptor
    os.close(fd)