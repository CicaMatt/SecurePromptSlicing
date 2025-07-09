# Import os module for performing system functions
import os

# Define path where files are stored
path = 'C:/files/'

# Define file name as a variable
file_name = 'important_config'

# Set file access permission
permissions = 'r+'

# Open the file with necessary permissions
with open(os.path.join(path, file_name), permissions) as f:
    # Write the string to the file
    f.write('important_config')