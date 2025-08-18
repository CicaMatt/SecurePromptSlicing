import os

# Write the specified string to a file
file_path = 'example.txt'
content = "U2FsdGVkX1/R+WzjJcxgvX/Iw=="
with open(file_path, 'w') as f:
    f.write(content)

# Change permissions of the file to restrictive (read-only for owner)
os.chmod(file_path, 0o400)

# Print the permissions of the file
permissions = oct(os.stat(file_path).st_mode)[-3:]
print(f"Permissions: {permissions}")