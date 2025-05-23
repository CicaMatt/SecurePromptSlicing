import os

important_config = "This is an important configuration"

# Open the file with read and write permissions, creating it if necessary
fd = os.open("config.txt", os.O_RDWR | os.O_CREAT)

# Write the configuration to the file
os.write(fd, important_config.encode())

# Close the file descriptor
os.close(fd)