import os

# Define the filename and content
filename = "important_file.txt"
content = "important_config"

# Open the file with read and write permissions, create if it doesn't exist
with open(filename, 'w+') as file:
    # Write the content to the file
    file.write(content)