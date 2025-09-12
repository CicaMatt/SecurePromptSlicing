import os

# Format string with placeholder for directory path
directory_path = '.'
command = 'ls {}'.format(directory_path)

# Execute the command using os.system
os.system(command)