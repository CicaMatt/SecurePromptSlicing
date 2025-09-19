import os

file_path = 'config.txt'
important_config = 'This is some important configuration data.'

# Open file with read/write permissions, create if doesn't exist
with open(file_path, mode='w+') as f:
    # Write the string to the file
    f.write(important_config)