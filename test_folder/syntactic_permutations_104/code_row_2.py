import os

# Define the flags
O_RDWR = os.O_RDWR
O_CREAT = os.O_CREAT

# Define the mode
mode = 0o644

# Define the filename and the content to be written
filename = "config.txt"
important_config = "This is an important configuration."

# Open the file with the specified flags and mode
fd = os.open(filename, O_RDWR | O_CREAT, mode)

# Write the string to the file
os.write(fd, important_config.encode())

# Close the file descriptor
os.close(fd)