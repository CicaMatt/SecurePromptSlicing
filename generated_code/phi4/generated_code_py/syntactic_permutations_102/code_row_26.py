import os

# Define the filename
filename = 'important_config'

# Open or create the file with appropriate permissions
with open(filename, mode='w+', 
          encoding='utf-8', 
          errors='ignore') as file:
    # Write the string to the file
    file.write('important_config')