import os

file_path = "important_config.txt"

# Open the file with read/write permissions, create if it doesn't exist
with open(file_path, 'w+') as file:
    # Write the string "important_config" to the file
    file.write("important_config")