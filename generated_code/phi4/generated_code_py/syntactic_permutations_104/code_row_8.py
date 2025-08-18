import os

# Define the file path and content to write
file_path = 'config.txt'
content_to_write = 'important_config'

# Open the file for reading and writing, create it if it doesn't exist
with open(file_path, 'w+') as file:
    # Write the specified string to the file
    file.write(content_to_write)