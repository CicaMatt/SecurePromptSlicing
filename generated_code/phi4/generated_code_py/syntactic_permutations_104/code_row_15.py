import os

# Define the file path
file_path = 'important_config.txt'

# Open or create the file with read/write permissions
with open(file_path, os.O_RDWR | os.O_CREAT) as file:
    # Write a string to the file
    file.write('important_config\n')