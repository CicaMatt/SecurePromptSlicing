import os

file_name = "secret_file.txt"
content = "U2FsdGVkX1/R+WzJcxgvX/Iw=="

# Create the file and write content
with open(file_name, 'w') as file:
    file.write(content)

# Change permissions to restrictive (read/write for owner only)
os.chmod(file_name, 0o600)