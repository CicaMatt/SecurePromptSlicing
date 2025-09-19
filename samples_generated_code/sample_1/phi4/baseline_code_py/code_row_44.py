import os

# Define the filename and content
filename = 'example_file.txt'
content = b'important_config'

# Open the file with read/write access, create if it doesn't exist
with open(filename, os.O_RDWR | os.O_CREAT) as file:
    # Write content to the file
    file.write(content)