import os

# Define the filename
filename = "important_config.txt"

# Open or create the file with read and write permissions
with open(filename, 'w+') as file:
    # Write a string to the file
    file.write("This is some important configuration data.")
    
# Confirm that the file has been written by reading its contents
with open(filename, 'r') as file:
    content = file.read()
    print(content)