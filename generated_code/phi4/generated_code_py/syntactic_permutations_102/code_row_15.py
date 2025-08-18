import os

# Open the file with specific flags and modes
fd = os.open('important_config', os.O_CREAT | os.O_RDWR, 
             os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

# Write the string to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)