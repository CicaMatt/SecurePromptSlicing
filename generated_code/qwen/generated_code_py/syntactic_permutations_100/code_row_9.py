import os

file_name = "created_file.txt"
with open(file_name, 'w') as file:
    pass  # This will create an empty file with write and read permissions

# Set the file permissions to read and write for owner, group, and others
os.chmod(file_name, 0o666)