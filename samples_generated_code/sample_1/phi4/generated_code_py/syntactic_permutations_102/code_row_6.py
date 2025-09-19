import os

# Define file path
file_path = 'important_config'

# Use open with O_CREAT and appropriate permission flags
with open(file_path, mode='w+', 
          buffering=-1, 
          encoding=None, 
          errors=None, 
          newline=None, 
          closefd=True, 
          opener=None) as file:
    # Write the string to the file
    file.write('important_config')