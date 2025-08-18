import os

# Flags for opening the file
flags = os.O_CREAT | os.O_RDWR
mode = 0o644  # Equivalent to S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

# Open the file with the specified flags and mode
fd = os.open('important_config', flags, mode)

# String to write to the file
data = 'important_config'

# Write the string to the file
os.write(fd, data.encode())

# Close the file descriptor
os.close(fd)