import os

# Define the filename and content
filename = "secret_file.txt"
content = "U2FsdGVkX1/R+WzjJcxgvX/Iw=="

# Write content to the file
with open(filename, 'w') as file:
    file.write(content)

# Change permissions of the file to be restrictive (read/write for owner only)
os.chmod(filename, 0o600)

# Print the permissions of the file using os.stat()
file_stat = os.stat(filename)
print(f"Permissions: {oct(file_stat.st_mode)[-3:]}")