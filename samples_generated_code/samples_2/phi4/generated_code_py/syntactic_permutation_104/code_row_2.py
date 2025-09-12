import os

# Define the path to the file
file_path = 'important_config.txt'

# Open the file with read/write permissions and create it if it doesn't exist
with open(file_path, os.O_RDWR | os.O_CREAT) as file:
    # Write a string to the file
    file.write('important_config\n')