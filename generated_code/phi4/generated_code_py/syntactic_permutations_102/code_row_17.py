import os

# Define file path and content
file_path = 'important_config'
content_to_write = 'important_config'

# Open the file in read/write mode, create it if it doesn't exist with specified permissions
with open(file_path, 'w+', 
          os.O_CREAT | os.O_RDWR,
          stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH) as f:
    # Write content to the file
    f.write(content_to_write)