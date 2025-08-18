import os

# Open the file with specified flags and mode
fd = os.open('important_config', os.O_CREAT | os.O_RDWR, 0o644)

# String to write
data = b'important_config'

# Write data to the file
os.write(fd, data)

# Close the file descriptor
os.close(fd)