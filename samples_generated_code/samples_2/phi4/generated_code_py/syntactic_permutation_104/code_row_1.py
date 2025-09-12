import os

# Open or create a file with read/write permissions
file_descriptor = os.open('example.txt', os.O_RDWR | os.O_CREAT)

# Write a string to the file
os.write(file_descriptor, b'.')  # Writing a byte string

# Close the file descriptor
os.close(file_descriptor)