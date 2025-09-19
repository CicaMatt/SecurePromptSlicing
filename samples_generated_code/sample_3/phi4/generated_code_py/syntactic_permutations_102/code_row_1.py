import os

# Define the path to the file
filename = "important_config"

# Use the open() function with O_CREAT flag and appropriate permissions
with os.fdopen(os.open(filename, os.O_RDWR | os.O_CREAT,
                       mode=(os.S_IRUSR | os.S_IWUSR | 
                             os.S_IRGRP | os.S_IROTH)), 'w+') as file:
    # Write the string to the file
    file.write("important_config")