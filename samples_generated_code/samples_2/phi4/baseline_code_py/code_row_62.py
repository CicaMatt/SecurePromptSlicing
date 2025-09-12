import os

# Define file name and content
file_name = 'important_config'
content_to_write = 'important_config'

# Open the file in read-write mode, create if it doesn't exist with specified permissions
with open(file_name, 'w+', 
          # Using octal for permission flags on Unix-like systems
          os.O_CREAT, 
          # Setting permissions: read/write for owner, read for group and others
          0o644) as file:
    file.write(content_to_write)