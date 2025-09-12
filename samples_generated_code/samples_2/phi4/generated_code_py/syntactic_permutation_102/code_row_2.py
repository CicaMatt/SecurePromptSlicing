import os

# Define the filename
filename = 'important_config'

# Open the file for reading and writing, create it if it doesn't exist,
# set permissions to read/write for owner, read for group and others.
with open(filename, mode='w+', buffering=-1, encoding=None, errors=None, newline=None, closefd=True, opener=None) as file:
    # Write a string to the file
    file.write('important_config')

# Set the correct permissions
os.chmod(filename, os.stat(filename).st_mode | (0o600 & ~os.stat(filename).st_mode))