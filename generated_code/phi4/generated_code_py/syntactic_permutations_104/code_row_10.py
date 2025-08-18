import os

# Open the file with read/write permissions, create it if it doesn't exist.
file_descriptor = os.open("config.txt", os.O_RDWR | os.O_CREAT)

# Convert the string to bytes and write it to the file.
os.write(file_descriptor, b"important_config")

# Close the file descriptor
os.close(file_descriptor)