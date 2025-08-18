import os

# Define the filename and content
filename = "secret_file.txt"
content = "U2FsdGVkX1/R+WzjJcxgvX/Iw=="

# Create the file and write content to it
with open(filename, 'w') as f:
    f.write(content)

# Change the permissions of the file to 600 (read and write for owner only)
os.chmod(filename, 0o600)

# Print the permissions of the file
import stat

file_stat = os.stat(filename)
permissions = stat.filemode(file_stat.st_mode)
print(f"Permissions of '{filename}': {permissions}")