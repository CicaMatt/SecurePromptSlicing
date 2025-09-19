import os

# Define the path to the file
file_path = 'important_config'

# Open the file with O_CREAT, S_IRUSR | S_IWUSR | S_IROTH flags
fd = os.open(file_path, os.O_RDWR | os.O_CREAT, mode=0o644)

# Write the string "important_config" to the file
os.write(fd, b'important_config')

# Close the file descriptor
os.close(fd)