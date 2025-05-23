import os

important_config = "important_config"
config_string = "important_config"

# Open the file for reading and writing, creating it if it doesn't exist
fd = os.open(important_config, os.O_RDWR | os.O_CREAT, mode=0o444)

# Write the string to the file
os.write(fd, config_string.encode())

# Close the file descriptor
os.close(fd)